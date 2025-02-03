#if defined(TILES)
#include "sdl_gamepad.h"
#include "debug.h"

#define dbg(x) DebugLog((x),D_SDL) << __FILE__ << ":" << __LINE__ << ": "

namespace gamepad
{

static constexpr int max_triggers = 2;
static constexpr int max_sticks = 2;
//constexpr int max_axis = 6;
static constexpr int max_buttons = 30;

static std::array<int, max_triggers> triggers_axis = {
    SDL_CONTROLLER_AXIS_TRIGGERLEFT,
    SDL_CONTROLLER_AXIS_TRIGGERRIGHT
};
static std::array<std::array<int, 2>, max_sticks> sticks_axis = { {
        { {SDL_CONTROLLER_AXIS_LEFTX,  SDL_CONTROLLER_AXIS_LEFTY}  },
        { {SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY} }
    }
};

static std::array<int, max_triggers> triggers_state = {0, 0};
static std::array<int, max_sticks> sticks_state = {0, 0};

static int triggers_threshold = 16000;
static int sticks_threshold = 16000;
static int error_margin = 2000;

static std::array<std::array<int, 16>, max_sticks> sticks_map = {};
static std::array<int, max_triggers> triggers_map = {0};
static std::array<int, max_buttons> buttons_map = {0};

struct task_t {
    Uint32 when;
    int button;
    int counter;
    int state;
};

static constexpr int max_tasks           = max_buttons + max_sticks + max_triggers + 1;
//constexpr int buttons_task_index  = 0;
static constexpr int sticks_task_index   = max_buttons;
static constexpr int triggers_task_index = max_buttons + max_sticks;

static std::array<task_t, max_tasks> all_tasks;

static int repeat_delay = 400;
static int repeat_interval = 200;
static int diagonal_detect_delay = 0;

// SDL related stuff
static SDL_TimerID timer_id;
static SDL_GameController *controller = nullptr;

static Uint32 timer_func( Uint32 interval, void * )
{
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_GAMEPAD_SCHEDULER;
    userevent.code = 0;
    userevent.data1 = nullptr;
    userevent.data2 = nullptr;

    event.type = SDL_GAMEPAD_SCHEDULER;
    event.user = userevent;

    SDL_PushEvent( &event );
    return interval;
}

void init()
{
    // FIXME maybe stick/trigger "buttons" need their own names?
    /*sticks_map[0][0b0001] = JOY_UP;
    sticks_map[0][0b0010] = JOY_RIGHT;
    sticks_map[0][0b0100] = JOY_DOWN;
    sticks_map[0][0b1000] = JOY_LEFT;
    sticks_map[0][0b0011] = JOY_RIGHTUP;
    sticks_map[0][0b0110] = JOY_RIGHTDOWN;
    sticks_map[0][0b1100] = JOY_LEFTDOWN;
    sticks_map[0][0b1001] = JOY_LEFTUP;

    sticks_map[1][0b0001] = JOY_21;
    sticks_map[1][0b0010] = JOY_22;
    sticks_map[1][0b0100] = JOY_23;
    sticks_map[1][0b1000] = JOY_24;
    sticks_map[1][0b0011] = JOY_25;
    sticks_map[1][0b0110] = JOY_26;
    sticks_map[1][0b1100] = JOY_27;
    sticks_map[1][0b1001] = JOY_28;

    triggers_map[0] = JOY_29;
    triggers_map[1] = JOY_30;

    for( int i = 0; i < max_buttons; ++i ) {
        buttons_map[i] = JOY_0 + i;
    }*/

    for( gamepad::task_t &task : all_tasks ) {
        task.counter = 0;
    }

    int ret = SDL_Init( SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER );
    if( ret < 0 ) {
        printErrorIf( ret != 0, "Init gamecontroller+timer failed" );
        return;
    }
    int numjoy = SDL_NumJoysticks();
    if( numjoy >= 1 ) {
        if( numjoy > 1 ) {
            dbg( D_WARNING ) <<
                             "You have more than one gamepads/joysticks plugged in, only the first will be used.";
        }
        controller = SDL_GameControllerOpen( 0 );
        printErrorIf( controller == nullptr, "SDL_GameControllerOpen failed" );
        if( controller ) {
            printErrorIf( SDL_GameControllerEventState( SDL_ENABLE ) < 0,
                          "SDL_GameControllerEventState(SDL_ENABLE) failed" );
        }
    } else {
        controller = nullptr;
        return;
    }

    timer_id = SDL_AddTimer( 50, timer_func, nullptr );
    printErrorIf( timer_id == 0, "SDL_AddTimer failed" );
}

void quit()
{
    if( timer_id ) {
        SDL_RemoveTimer( timer_id );
        timer_id = 0;
    }
    if( controller ) {
        SDL_GameControllerClose( controller );
        controller = nullptr;
    }
}

SDL_GameController *get_controller()
{
    return controller;
}

static int one_of_two( const std::array<int, 2> &arr, int val )
{
    if( arr[0] == val ) {
        return 0;
    }
    if( arr[1] == val ) {
        return 1;
    }
    return -1;
}

static void schedule_task( task_t &task, Uint32 when, int button, int state )
{
    task.when = when;
    task.button = button;
    task.counter = 1;
    task.state = state;
}

static void cancel_task( task_t &task )
{
    task.counter = 0;
}

static void send_input( int ibtn, input_event_t itype = input_event_t::gamepad )
{
    last_input = input_event( ibtn, itype );
}

static void dpad_changes( task_t &task, const std::array<int, 16> &m, Uint32 now, int old_state,
                          int new_state, int inc_state )
{
    // get rid of unneeded bits
    old_state &= 0b1111;
    new_state &= 0b1111;

    if( old_state == new_state ) {
        return;
    }

    switch( new_state ) {
        case SDL_HAT_LEFTUP:
        case SDL_HAT_LEFTDOWN:
        case SDL_HAT_RIGHTUP:
        case SDL_HAT_RIGHTDOWN:
            send_input( m[new_state] );
            schedule_task( task, now + repeat_delay, m[new_state], new_state );
            break;
        case SDL_HAT_CENTERED: {
            if( task.counter == 1 ) {
                switch( old_state ) {
                    // detecting quick CENTER -> Left|Up|Right|Down -> CENTER transition
                    case SDL_HAT_UP:
                    case SDL_HAT_DOWN:
                    case SDL_HAT_RIGHT:
                    case SDL_HAT_LEFT:
                        send_input( task.button + inc_state );
                }
            }
            cancel_task( task );
            break;
        }
        case SDL_HAT_UP:
        case SDL_HAT_DOWN:
        case SDL_HAT_RIGHT:
        case SDL_HAT_LEFT:
            schedule_task( task, now + diagonal_detect_delay, m[new_state], new_state );
            task.counter += old_state;
            break;
    }
}

void handle_axis_event( SDL_Event &event, int increment_keystate )
{
    if( event.type != SDL_CONTROLLERAXISMOTION ) {
        return;
    }

    int axis = event.caxis.axis;
    int value = event.caxis.value;

    // check triggers
    int idx = one_of_two( triggers_axis, axis );
    if( idx >= 0 ) {
        int state = triggers_state[idx];
        int button = triggers_map[idx];
        task_t &task = all_tasks[triggers_task_index + idx];
        if( !state && value > triggers_threshold + error_margin ) {
            if ( one_of_two( triggers_axis, axis ) != 0 ) { // Right trigger only
                send_input( button + increment_keystate );
            }
            triggers_state[idx] = 1;
        }
        if( state && value < triggers_threshold - error_margin ) {
            triggers_state[idx] = 0;
            cancel_task( task );
        }
        return;
    }

    // check sticks
    for( int i = 0; i < max_sticks; ++i ) {
        int idx = one_of_two( sticks_axis[i], axis );
        if( idx >= 0 ) {
            int stick_state;
            int old_state = sticks_state[i];
            int new_state = old_state;
            task_t &task = all_tasks[sticks_task_index + i];

            // calculate dpad state for the analog sticks, simulating joystick hat state (4 bits)
            if( idx ) { // vertical stick movement
                if( !( old_state & 0b0100 ) && value > sticks_threshold + error_margin ) {
                    new_state |= 0b0100;    // turn on bit _x__
                    stick_state = ( ( i > 0 ) ? 23 : 259 ) + increment_keystate; // stick down R/L
                    send_input( stick_state, input_event_t::gamepad );
                } else if( ( old_state & 0b0100 ) && value < sticks_threshold - error_margin ) {
                    new_state &= 0b1011;    // turn off bit _x__
                } else if( !( old_state & 0b0001 ) && value < -sticks_threshold - error_margin ) {
                    new_state |= 0b0001;    // turn on bit ___x
                    stick_state = ( ( i > 0 ) ? 21 : 257 ) + increment_keystate; // stick up R/L
                    send_input( stick_state, input_event_t::gamepad );
                } else if( ( old_state & 0b0001 ) && value > -sticks_threshold + error_margin ) {
                    new_state &= 0b1110;    // turn off bit ___x
                }
            } else { // horizontal stick movement
                if( !( old_state & 0b0010 ) && value > sticks_threshold + error_margin ) {
                    new_state |= 0b0010;    // turn on bit __x_
                    stick_state = ( ( i > 0 ) ? 22 : 258 ) + increment_keystate; // stick right R/L
                    send_input( stick_state, input_event_t::gamepad );
                } else if( ( old_state & 0b0010 ) && value < sticks_threshold - error_margin ) {
                    new_state &= 0b1101;    // turn off bit __x_
                } else if( !( old_state & 0b1000 ) && value < -sticks_threshold - error_margin ) {
                    new_state |= 0b1000;    // turn on bit x___
                    stick_state = ( ( i > 0 ) ? 24 : 260 ) + increment_keystate; // stick left R/L
                    send_input( stick_state, input_event_t::gamepad );
                } else if( ( old_state & 0b1000 ) && value > -sticks_threshold + error_margin ) {
                    new_state &= 0b0111;    // turn off bit x___
                }
            }

            sticks_state[i] = new_state;
            // Don't do dpad_changes because we only cardinals
            // dpad_changes( task, sticks_map[i], now, old_state, new_state, increment_keystate );
        }
    }
}

void handle_button_event( SDL_Event &event, int increment_keystate )
{
    
    int button = event.cbutton.button;
    int state = event.cbutton.state;
    Uint32 now = event.cbutton.timestamp;
    task_t &task = all_tasks[button];

    switch( event.type ) {
        case SDL_CONTROLLERBUTTONDOWN:
            if ( state ) {
                switch( button ) {
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        send_input( button ); // DPAD should be only buttons that can't be modified
                        schedule_task( task, now + repeat_delay, buttons_map[button], state );
                }
            } else {
                cancel_task( task );
            }
        case SDL_CONTROLLERBUTTONUP: {
            if( state ) {
                switch( button ) {
                    case SDL_CONTROLLER_BUTTON_GUIDE:
                        send_input( KEY_F( 1 ), input_event_t::keyboard_char );
                        break;
                    default:
                        send_input( button + increment_keystate );
                }
            } else {
                cancel_task( task );
            }
        }
    }
}

void handle_scheduler_event( SDL_Event &event )
{
    Uint32 now = event.user.timestamp;
    for( gamepad::task_t &task : all_tasks ) {
        if( task.counter && task.when <= now ) {
            send_input( task.button );
            task.counter += 1;
            task.when = now + repeat_interval;
        }
    }
}

} // namespace gamepad

#endif // TILES


#include <android/log.h>
#include <android_native_app_glue.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Numb3rs", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Numb3rs", __VA_ARGS__))

/**
 * Process the next main command.
 */
void android_handle_cmd(android_app* app, int32_t cmd)
{
	(void)app;
	switch (cmd)
	{
	case APP_CMD_INIT_WINDOW:
		// The window is being shown, get it ready.
		break;
	case APP_CMD_TERM_WINDOW:
		// The window is being hidden or closed, clean it up.
		break;
	case APP_CMD_GAINED_FOCUS:
		// When our app gains focus, we start monitoring the accelerometer.
		break;
	case APP_CMD_LOST_FOCUS:
		// When our app loses focus, we stop monitoring the accelerometer.
		// This is to avoid consuming battery while not being used.
		break;
	}
}

int android_handle_input(android_app* app, AInputEvent* event)
{
	(void)app;
	int handled = 0;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		LOGI("Registered %zu touches", AMotionEvent_getPointerCount(event));
		handled = 1;
	}

	return handled;
}

void android_main(struct android_app* state)
{
	state->onAppCmd     = android_handle_cmd;
	state->onInputEvent = android_handle_input;

	// Prepare to monitor accelerometer
	while (1)
	{
		// Read all pending events.
		int                  ident;
		int                  events;
		android_poll_source* source;

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
		{

			// Process this event.
			if (source != NULL)
			{
				source->process(state, source);
			}

			// Check if we are exiting.
			if (state->destroyRequested != 0)
			{
				LOGI("Destroy requested; exiting");
				return;
			}
		}
	}
}


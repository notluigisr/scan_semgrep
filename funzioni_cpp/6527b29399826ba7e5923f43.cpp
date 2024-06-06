evdev_pointer_notify_button(struct evdev_device *device,
			    uint64_t time,
			    unsigned int button,
			    enum libinput_button_state state)
{
	if (device->scroll.method == LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN &&
	    button == device->scroll.button) {
		evdev_button_scroll_button(device, time, state);
		return;
	}

	evdev_pointer_post_button(device, time, button, state);
}
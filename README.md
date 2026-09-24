[![Open Source AI Manifesto](https://human-oss.dev/badge.svg)](https://human-oss.dev)


> [!IMPORTANT]
> This project is still in alpha and only has implemented the `dxio_mc_3w` board with the `presonus_firestudio_project` audio device.


# Fuegocable XMOS Firmware

Firmware for XMOS chip-based boards that are used to modify Firewire audio interfaces to work with USB Audio.

## Project Architecture

```
xmos-firmware/
├── boards/                    # XMOS board implementations
│   └── dxio_mc_3w/           # DIYinhk DXIO MC (3W) board
│       ├── src/              # Board sources
│       │   ├── board.xc      # I2C/SPI/GPIO implementation
│       │   ├── board.h       # Board header
│       │   ├── board_gpio.h  # GPIO definitions
│       │   ├── board_gpio.c  # GPIO implementation
│       │   ├── audiohw.xc    # Hooks to lib_xua
│       │   ├── xua_conf.h    # Board XUA configuration
│       │   ├── xua_conf_globals.h # Global XUA declarations
│       │   ├── xua_conf_tasks.h # Board XUA tasks
│       │   └── dxio_mc_3w.xn # XMOS hardware description
│       └── CMakeLists.txt    # Build configuration
├── common/                    # Fuegocable shared code
│   ├── audio_device.h        # Common audio device interface
│   ├── audio_device_ui.c/h   # Common UI (LEDs, display)
│   ├── audio_devices/        # Audio device implementations
│   │   ├── presonus_firestudio_project/
│   │   └── raspberry_pi_dac_plus/
│   ├── drivers/             # Codec drivers (CS4385, CS5368, etc)
│   └── wrappers/            # I2C/SPI wrappers
├── sandbox/                  # Third-party XMOS libraries
└── CMakeLists.txt            # Root build configuration
```

## Key Concepts

### XMOS Boards
A **board** is the physical hardware based on an XMOS chip that runs the firmware. Each board has:
- Its own folder in `boards/`
- Port configuration (`.xn` file)
- Specific I2C, SPI, GPIO implementation
- Particular XUA configuration

### Audio Devices
An **audio device** is the Firewire audio interface that connects to the XMOS board (e.g., Presonus Firestudio Project, Focusrite Saffire). Each audio device has:
- Its own folder in `common/audio_devices/`
- Implementation of `audio_device.c` with initialization and configuration functions
- `audio_device_xua_conf.h` file with specific XUA configuration
- Corresponding codec drivers in `common/drivers/`

The audio device is selected at build-time via the CMake system. Each build configuration includes the sources for the corresponding audio device.

### XUA Configuration
The XUA (XMOS USB Audio) configuration defines how the firmware behaves as a USB Audio device. It consists of:
- `xua_conf.h`: Main configuration (channels, frequencies, features)
- `xua_conf_globals.h`: Global declarations and includes
- `xua_conf_tasks.h`: Tasks that run on each tile

The files `fc_xua_conf.h`, `fc_xua_conf_globals.h` and `fc_xua_conf_tasks.h` in `common/` provide the base configuration common to all boards. Each board can extend or override this configuration in its own files.

## Build System

The project uses CMake with support for multiple build configurations. Each board generates a build configuration for each supported audio device.

```bash
# Configure build
cmake -B build

# List available configurations
cmake --build build --target help

# Build for a specific board and audio device
cmake --build build --target dxio_mc_3w_presonus_firestudio_project
```

## Adding a New Board

1. Create folder `boards/<board_name>/src/`
2. Copy files from an existing board as a base
3. Modify `dxio_mc_3w.xn` → `<board_name>.xn` with the new board's ports
4. Adjust implementations in `board.xc`, `board_gpio.c/h` according to hardware
5. Configure `xua_conf.h`, `xua_conf_globals.h`, `xua_conf_tasks.h`
6. Create `CMakeLists.txt` in the board root (see dxio_mc_3w as an example)
7. Add `add_subdirectory(boards/<board_name>)` in the root `CMakeLists.txt`

## Adding a New Audio Device

1. Create folder `common/audio_devices/<device_name>/`
2. Create `audio_device.c` implementing:
   - `fc_audio_device_main()`
   - `fc_audio_device_hw_init()`
   - `fc_audio_device_hw_config_begin()`
   - `fc_audio_device_hw_config()`
   - `fc_audio_device_hw_config_end()`
   - `fc_audio_device_buffer_management_init()` (optional)
   - `fc_audio_device_buffer_management()` (optional)
3. Create `audio_device_xua_conf.h` with specific XUA configuration
4. Add necessary codec drivers in `common/drivers/`
5. The build system will automatically detect the new audio device

## Code Structure

### Separation of Responsibilities

- **boards/**: XMOS hardware-specific code (GPIO, I2C, SPI, ports)
- **common/audio_devices/**: Audio device-specific code (codecs, configuration, leds)
- **common/**: Code shared among all boards and audio devices

### Audio Device Interface

The file `common/audio_device.h` defines the interface that all audio devices must implement. This allows any board to work with any audio device without modifying the board code.

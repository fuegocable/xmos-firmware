
// TODO: implement DFU so we can detect fuegocable firmware version beyond any brand specific vid/pid override that we do.
// For example, Presonus Firestudio Project presents itself as an Audiobox 1818 VSL device, so we override the BCD_DEVICE
// in order to not show a warning in Universal Control windows driver, but this way we also lose track of our own firmware
// version when using DFU.

#define FC_VERSION_MAJOR (1)
#define FC_VERSION_MINOR (0)
#define FC_VERSION_PATCH (0)
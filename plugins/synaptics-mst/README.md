---
title: Plugin: Synaptics MST
---

## Introduction

This plugin supports querying and flashing Synaptics MST hubs used in Dell systems
and docks.

## Firmware Format

The daemon will decompress the cabinet archive and extract a firmware blob in
an unspecified binary file format.

This plugin supports the following protocol ID:

* `com.synaptics.mst`

## GUID Generation

These devices use custom GUID values, e.g.

* `MST-$(board-ID)`
* `MST-$(device_kind)-$(chip-ID)-$(board-ID)`
* `MST-$(device_kind)-$(board-ID)`
* `MST-$(device_kind)`

Please refer to the plugin source for more details about how the GUID is
constructed for specific hardware.

## Update Behavior

The firmware is deployed when the device is in normal runtime mode, and the
device will reset when the new firmware has been written. On some hardware the
MST device may not enumerate if there is no monitor actually plugged in.

## Vendor ID Security

The vendor ID is set from the PCI vendor, for example set to `DRM_DP_AUX_DEV:0x$(vid)`

## Requirements

### (Kernel) DP Aux Interface

Kernel 4.6 introduced an DRM DP Aux interface for manipulation of the registers
needed to access an MST hub.
This patch can be backported to earlier kernels:
<https://github.com/torvalds/linux/commit/e94cb37b34eb8a88fe847438dba55c3f18bf024a>

## Usage

Supported devices will be displayed in `# fwupdmgr get-devices` output.

Here is an example output from a Dell WD15 dock:

```text
Dell WD15/TB16 wired Dock Synaptics VMM3332
  Guid:                 653cd006-5433-57db-8632-0413af4d3fcc
  DeviceID:             MST-1-1-0-0
  Plugin:               synaptics_mst
  Flags:                allow-online
  Version:              3.10.002
  Created:              2017-01-13
  Modified:             2017-01-13
  Trusted:              none
```

Payloads can be flashed just like any other plugin from LVFS.

## Supported devices

Not all Dell systems or accessories contain MST hubs.
Here is a sample list of systems known to support them however:

* Dell WD15 dock
* Dell TB16 dock
* Dell TB18DC
* Latitude E5570
* Latitude E5470
* Latitude E5270
* Latitude E7470
* Latitude E7270
* Latitude E7450
* Latitude E7250
* Latitude E5550
* Latitude E5450
* Latitude E5250
* Latitude Rugged 5414
* Latitude Rugged 7214
* Latitude Rugged 7414

## External Interface Access

This plugin requires read/write access to `/dev/drm_dp_aux*`.

## Version Considerations

This plugin has been available since fwupd version `1.3.6`.

## Data Flow

```mermaid
  flowchart LR
      subgraph MST Controller
        MST(Controller)
        SPI[(SPI)]
      end
      subgraph Kernel
        gpu(GPU\ndriver)
      end
      subgraph fwupd Process
        fwupdengine(FuEngine)
        mst_plugin(Synaptics MST\nPlugin)
      end
      fwupdengine-->mst_plugin
      mst_plugin<--/dev/drm_dp_aux-->gpu
      gpu<--DDC/I2C-->MST
      MST---SPI
```

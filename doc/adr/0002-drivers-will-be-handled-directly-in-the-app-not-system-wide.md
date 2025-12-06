# 2. Drivers will be handled directly in the app, not system wide

Date: 2025-12-06

## Status

Accepted

## Context

The OS needs to drive, as a minimum, a keyoard and a display.

## Decision

Rather than writing or using a driver for linux for the display and keyboard, we will write custom drivers.

## Consequences

* Simpler solution means less complicated code.
* We will not be able to use the hardware outside of the phone operating system

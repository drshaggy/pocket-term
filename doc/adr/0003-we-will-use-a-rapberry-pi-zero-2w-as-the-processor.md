# 3. We will use a Rapberry Pi Zero 2W as the processor

Date: 2025-12-06

## Status

Accepted

## Context

What hardware will we write our Phone Operating System for?

## Decision

We will use a raspberry pi zero 2w board for the processor

## Consequences

* The form factor is small, keeping the overall device small
* Cheap
* GPIO headers make for essy connectivity
* Full linux - A lot of the OS work is done for us
* Can leverage a terminal
* Built in bluetooth and wifi with drivers

* Raspberry Pi draws more power than ESP32
* A lot of overhead of the functionality we need

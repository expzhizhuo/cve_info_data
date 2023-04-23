# Double Free Issue Report

> https://github.com/virtualsquare/picotcp/issues/6



I found a security issue in picoTCP v1.7.0 and picoTCP-NG v2.1. It's a double free bug in function `pico_fragments_reassemble` (Line 362 and Line 364 in [modules/pico_fragments.c ](https://github.com/virtualsquare/picotcp/blob/f336ead9c79c8d6c53f6b4d060f46413bfcfcf7b/modules/pico_fragments.c#L362)).

In function `pico_transport_receive`, when the switch goes into a default branch, it would release `f` (Line 239 in [`stack/pico_stack.c`](https://github.com/virtualsquare/picotcp/blob/f336ead9c79c8d6c53f6b4d060f46413bfcfcf7b/stack/pico_stack.c#L239)) and return -1. However, after -1 have been return from `pico_transport_receive(full, proto)` (Line 362 in [`modules/pico_fragments.c`](https://github.com/virtualsquare/picotcp/blob/f336ead9c79c8d6c53f6b4d060f46413bfcfcf7b/modules/pico_fragments.c#L362)), another `pico_frame_discard(full)`(Line 364 in [`modules/pico_fragments.c`](https://github.com/virtualsquare/picotcp/blob/f336ead9c79c8d6c53f6b4d060f46413bfcfcf7b/modules/pico_fragments.c#L364)) would be called and `pico_frame_discard` release `full` again. This leads a double free bug.
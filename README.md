# audio-route-config
Configure ALSA mixer controls from Android `mixer_paths.xml`. It uses the Android audio_route library to load and apply audio routes.

#### Usage:
```
audiorouteconfig [-d device] [-f mixer_path.xml] route0 route1 .. routeN
```
```
-d      Sound card device number
-f      Path to mixer_paths.xml
routeN  Audio route name. Applied in order of appearance.
```

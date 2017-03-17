This example is the simplest possible implementation of a paint program. Its main use is to demonstrate how rendering on a QOpenGLWidget can be done in a non-GUI thread by properly swaping the context back and forth between the main GUI thread and the rendering thread. In the case of a paint program like this one, such functionality enables capturing of more tablet events, resulting in smoother curves. 

The functionality demonstrated in this example is needed when the paint program is used with graphic tablets with unreliable drivers. For example, the Huion H610 pro, when used with Qt on the mac, exhibits a weird behavior when tablet events are not being processed fast enough. Offloading the rendering to a separate thread allows for very fast handling of all tablet events and the tablet behaves.

This program has only been tested with a Huion H610 pro and Qt 5.8 on macOS 10.12.

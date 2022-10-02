## Ray tracing in one weekend in cpp

This is my implementation of the [Ray tracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) challange in cpp.

## Developer Notes

- I haven't used cpp before. I rely on Copilot heavily.
- I don't know if I'm doing it right. I'm just trying to get it done.
- I'm not sure if I'm using the correct or the best compiler. I just tried them all and picked the best one that works with vscode.
- Performance or the best practices are not the scope of this challange it's just a beginner's challange.

## Usage

### Build

I've used Cmake to make the project. And spent some time to make sure i can work with Visual Studio Code. Just grab the [Cmake extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) and you're good to go.


### File output

The original challange includes ppm files. You can use [VScode ppm viewer](https://marketplace.visualstudio.com/items?itemName=lextudio.reveal-in-ppm-viewer) to view the output.

I haven't added any arguments for changing output file etc. You can change the output file in the code. Default is `image.ppm`.
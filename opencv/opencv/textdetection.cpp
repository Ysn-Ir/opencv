#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main() {
    // Initialize tesseract
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init(nullptr, "eng.traineddata")) { // "eng" for English, replace with your desired language
        std::cerr << "Could not initialize tesseract." << std::endl;
        return 1;
    }

    // Open the image file
    Pix* image = pixRead("txt.png"); // Replace "example_image.png" with your image path
    api->SetImage(image);

    // Perform OCR
    char* outText = api->GetUTF8Text();
    std::cout << "OCR Output:" << std::endl;
    std::cout << outText << std::endl;

    // Clean up
    delete[] outText;
    pixDestroy(&image);
    api->End();

    return 0;
}

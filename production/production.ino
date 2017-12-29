
#include <SPI.h>
#include <SD.h>

//  Sensor initializations
File finalFile;
File fileA;
File fileB;
File fileC;

void setup()
{
    Serial.begin(9600);

    pinMode(6, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    //  Check SD
    Serial.print("Initializing SD card...");
    if (!SD.begin(10)) {
        Serial.println("Initialization failed!");
        return;
    }
    Serial.println("Initialization done.");

    SD.remove("final.csv");
    SD.remove("fileA.csv");
    SD.remove("fileB.csv");
    SD.remove("fileC.csv");
    finalFile = SD.open("final.csv", FILE_WRITE);
    fileA = SD.open("fileA.csv", FILE_WRITE);
    fileB = SD.open("fileB.csv", FILE_WRITE);
    fileC = SD.open("fileC.csv", FILE_WRITE);

   /*******************************************************   
   *Read from the sensors until the off button is pressed
   *******************************************************/
    if (finalFile) {
        while (digitalRead(6) == 0) {
            if (analogRead(A6)) {
                fileA.print(analogRead(A6));
                fileA.print(",");
            }
            if (analogRead(A5)) {
                fileB.print(analogRead(A5));
                fileB.print(",");
            }
            if (analogRead(A4)) {
                fileC.print(analogRead(A4));
                fileC.print(",");
            }
        }
        // close the file:
        Serial.println("button pressed");
        fileA.close();
        fileB.close();
        fileC.close();
    }
    else {
        // If the file didn't open, print an error:
        Serial.println("Error in block 1");
    }

  
   /*******************************************************   
   * Final file creation
   *******************************************************/
    finalFile = SD.open("final.csv", FILE_WRITE);
    fileA = SD.open("fileA.csv");
    fileB = SD.open("fileB.csv");
    fileC = SD.open("fileC.csv");

    if (finalFile && fileA && fileB && fileC) {
        Serial.println("\nCreating final file");

        while (fileA.available()) {
            finalFile.write(fileA.read());
        }
        finalFile.write("\n");
        Serial.println("A written");

        while (fileB.available()) {
            finalFile.write(fileB.read());
        }
        finalFile.write("\n");
        Serial.println("B written");

        while (fileC.available()) {
            finalFile.write(fileC.read());
        }
        finalFile.write("\n");
        Serial.println("C written");
    }
    else {
        Serial.println("Error in block 3");
    }
    finalFile.close();
}

void loop()
{
    // Nothing happens here
}


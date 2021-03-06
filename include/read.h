void execReader()
{
    // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++)
        key.keyByte[i] = 0xff;

    //some variables we need
    byte block;
    byte len;
    MFRC522::StatusCode status;

    //-------------------------------------------

    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }

    Serial.println(F("**Card Detected:**"));

    //-------------------------------------------

    mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

    // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

    //-------------------------------------------

    byte buffer1[18];

    block = 1;
    len = 18;

    //------------------------------------------- GET NIM
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        Serial.println(F("\n**End Reading**\n"));

        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
        return;
    }

    status = mfrc522.MIFARE_Read(block, buffer1, &len);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        Serial.println(F("\n**End Reading**\n"));

        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
        return;
    }

    // buzzer
    tone(buzzer, 5000); // Send 1KHz sound signal...
    digitalWrite(led, HIGH);
    delay(100);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    digitalWrite(led, LOW);

    delay(50);        // ...for 1 sec

    tone(buzzer, 5000); // Send 1KHz sound signal...
    digitalWrite(led, HIGH);
    delay(100);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    digitalWrite(led, LOW);


    // unsigned long uid;

    
    // Serial.print(F("UID: "));
    
    // uid = mfrc522.uid.uidByte[0];
    // Serial.print(uid);
    // Keyboard.print(uid);

    // uid = mfrc522.uid.uidByte[1];
    // Serial.print(uid);
    // Keyboard.print(uid);

    // uid = mfrc522.uid.uidByte[2];
    // Serial.print(uid);
    // Keyboard.print(uid);

    // uid = mfrc522.uid.uidByte[3];
    // Serial.print(uid);
    // Keyboard.print(uid);

    // Serial.println("");
    // Keyboard.press(KEY_TAB);
    // Keyboard.release(KEY_TAB);
    // Keyboard.press(KEY_F2);
    // Keyboard.release(KEY_F2);

    //PRINT NIM
    char var;
    String nim;

    Serial.print(F("NIM: "));

    for (uint8_t i = 0; i < 16; i++)
    {
        if (buffer1[i] != 32)
        {
            var = buffer1[i];
            if (var != '\n' && var != '\r') {
                nim.concat(String(var));
            }
            
            Serial.print(String(var));
            String temp = String(var);
            Keyboard.print(temp);
        }
    }

    // Serial.print(nim);
    // Keyboard.print(nim);
    Keyboard.println("");

    Serial.println(F("\n**End Reading**\n"));

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}
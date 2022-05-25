using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bootloader
{
    internal class MHexParser
    {
        // Zmienne do parsowania.
        public string mHex = "";
        public string [] mHexLines = null;
        public UInt32 mCurAddr = 0;

        System.IO.Ports.SerialPort mptrCOM = null;  // Wskaźnik na port szeregowy - do wysyłania ramek.

        public List<MDataPacket> mlDataPackets = new List<MDataPacket>();  // Lista danych pobranych z pliku hex.
        public int mdataSentCnt = 0;   // Licznik wysłanych paczek danych.
        public bool mIsAnsReceived = true;


        // Dokumentacja ramek
        // { --------- HEADER --------- }  {DATA}  {FOOTER}
        //  START  TYPE  ADDR  DATA_SIZE    DATA    END

        // Definicje ramek
        private const byte FRAME_START = 0xA5;
        private const byte FRAME_END = 0xFF;

        // Pozycje - zaktualizować w przypadku zmiany ramki
        public  const int FRAME_POS_TYPE = 1;       // Numer bajtu w którym znajduje się typ ramki.
        public  const int FRAME_POS_ADDR = 2;       // Numer bajtu w którym znajduje się adres.
        public  const int FRAME_POS_DATASIZE = 3;   // Numer bajtu w którym znajduje się wartość określająca ilość danych.

        private const int HEADER_SIZE = 4;          // Ilość bajtów nagłówka.

        private const byte FRAME_TYPE_BootloaderStart = 0xB0;
        private const byte FRAME_TYPE_WriteFlash = 0xB1;
        public  const byte FRAME_TYPE_ReadFlash = 0xB2;
        private const byte FRAME_TYPE_BootloaderProgOk = 0xB3;
        private const byte FRAME_TYPE_BootloaderStop = 0xB4;
        private const byte FRAME_TYPE_AppStart = 0xB5;

        public MHexParser(System.IO.Ports.SerialPort ptrCOM)
        {
            mptrCOM = ptrCOM;
        }

        // ---------- RAMKI ----------
        public void sendFrame_BootloaderStart(byte addr)    // Wyślij ramkę oznaczającą rozpoczęcie wysyłania programu.
        {
            int dataLen = 0;

            byte[] buffer = new byte[] {FRAME_START, 
                                        FRAME_TYPE_BootloaderStart, 
                                        addr,
                                        (byte)dataLen, 

                                        FRAME_END};

            mptrCOM.Write(buffer, 0, buffer.Length);

            displayFrame(buffer);
        }

        public void sendFrame_WriteFlash()  // Wyślij ramkę zawierającą fragment programu.
        {
            MDataPacket packet = mlDataPackets[mdataSentCnt];  // Pobierz pakiet do wysłania.
            int dataLen = packet.mData.Length;

            // Stwórz początek ramki.
            byte[] buffer = new byte[HEADER_SIZE + dataLen + 1];

            buffer[0] = FRAME_START;
            buffer[1] = FRAME_TYPE_WriteFlash;
            buffer[2] = (byte)packet.mAddr;
            buffer[3] = (byte)dataLen;

            // Dopisz dane z pakietu.
            for (int i = 0; i < dataLen; i++)
            {
                buffer[HEADER_SIZE + i] = packet.mData[i];
            }

            // Zakończ ramkę i wyślij.
            buffer[buffer.Length - 1] = FRAME_END;

            mptrCOM.Write(buffer, 0, buffer.Length);

            // Przesuń się na następną ramkę.
            mdataSentCnt++;

            displayFrame(buffer);
        }

        public void sendFrame_BootloaderProgOk()    // Wyślij ramkę zakończającą wysyłanie programu.
        {
            int dataLen = 0;
            byte addr = 0x00;

            byte[] buffer = new byte[] {FRAME_START, 
                                        FRAME_TYPE_BootloaderProgOk, 
                                        addr,
                                        (byte)dataLen, 

                                        FRAME_END};

            mptrCOM.Write(buffer, 0, buffer.Length);

            displayFrame(buffer);
        }

        public void sendFrame_BootloaderStop()  // Wyślij ramkę przerywającą wysyłanie programu.
        {
            int dataLen = 0;
            byte addr = 0x00;

            byte[] buffer = new byte[] {FRAME_START, 
                                        FRAME_TYPE_BootloaderStop, 
                                        addr,
                                        (byte)dataLen, 

                                        FRAME_END};

            mptrCOM.Write(buffer, 0, buffer.Length);

            displayFrame(buffer);
        }

        public void sendFrame_AppStart()    // Wyślij ramkę rozpoczynającą wykonywanie wysłanego programu.
        {
            int dataLen = 0;
            byte addr = 0x00;

            byte[] buffer = new byte[] {FRAME_START, 
                                        FRAME_TYPE_AppStart, 
                                        addr,
                                        (byte)dataLen, 

                                        FRAME_END};

            mptrCOM.Write(buffer, 0, buffer.Length);

            displayFrame(buffer);
        }

        public void readFrame_ReadFlash(byte[] frame)    // Odbierz ramkę, która przyszła po wysłaniu fragmentu programu.
        {
            MDataPacket a = mlDataPackets[mdataSentCnt - 1];    // Pobierz poprzednio wysłany pakiet.

            byte[] data = { };

            for (int i = 0; i < frame[FRAME_POS_DATASIZE]; i++)
            {
                data[i] = frame[i];
            }

            MDataPacket b = new MDataPacket(frame[FRAME_POS_ADDR], data);   // Stwórz nowy pakiet z odebranych danych.

            if (a != b)
            {
                Form1.mConsoleText += "Wysłany pakiet nie zgadza się z odebranym!\r\n";
                Form1.mIsToRedraw = true;
                Form1.mMode = Form1.Mode.Error;
            }

            displayFrame(data, false);
        }

        public void displayFrame(byte[] buffer, bool isSending = true)  // Wyświetl ramkę w konsoli.
        {
            if (isSending)
                Form1.mConsoleText += "\r\n---------- WYSŁANO ----------\r\n";
            else
                Form1.mConsoleText += "\r\n---------- ODEBRANO ----------\r\n";

            string temp = 
                "{" + 
                BitConverter.ToString(buffer, 0, HEADER_SIZE) + 
                "} [" + 
                BitConverter.ToString(buffer, HEADER_SIZE, buffer.Length - HEADER_SIZE - 1) +
                "] {" + 
                BitConverter.ToString(buffer, buffer.Length - 1) + 
                "}";

            Form1.mConsoleText += temp.Replace("-", " ");
            Form1.mConsoleText += "\r\n-----------------------------\r\n";
            Form1.mIsToRedraw = true;
        }

        // ---------- OPERACJE ----------
        public void readFile(string fileName )
        {
            string mHex = System.IO.File.ReadAllText( fileName );

            char[] delims = new[] { '\r', '\n' };
            mHexLines = mHex.Split(delims, System.StringSplitOptions.RemoveEmptyEntries);
        }

        public void parseFile(string fileName)
        {
            this.readFile(fileName);
            int cnt = mHexLines.Length;
            for( int i =0; i<cnt; i++)
            {
                MDataPacket packet = this.parseLine(i);
                if (!(packet is null))
                {
                    mlDataPackets.Add(packet);
                }
            }
        }

        public MDataPacket parseLine(int index)
        {
            string str = mHexLines[index];
            int cnt = str.Length;
            if (str[0] != ':') throw new System.ArgumentException( "Hex nie zaczyna sie od :" );

            byte[] v = lineToArray( index );

            {
                int cnt2 = v.Length;
                byte cntHex = v[0];
                UInt16 addr = (UInt16)((v[1] << 8) | v[2]);
                byte type = v[3];
                byte[] dane = new byte[cntHex];
                for (int i = 0; i < cntHex; i++)  dane[i] = v[i+4];
                byte crc = v[cnt2 - 1];

                int crcSum = 0;
                for( int i = 0; i < cnt2-1; i++ ) crcSum += v[i];
                crcSum = (0x100 - (byte)crcSum);
                crcSum &= 0xFF;

                if( crcSum != crc )
                    throw new System.ArgumentException("HEX CRC nie dziala:" + index.ToString());

                // type: 00=dane; 01=ostatni rekord/koniec pliku
                //       02=adres 20bit(adr<<4); 03=adresCS 20 bit;
                //       04=adres 32bit(addr<<16); 05=adresCS 32bit

                if ((type == 0x00) || (type == 01))
                {
                    if (dane.Length <= 0) return null;

                    MDataPacket packet = new MDataPacket(mCurAddr + addr, dane, index);
                    return packet;

                }else if( type == 2) {
                    mCurAddr = (UInt32)((dane[0] << (8+4)) | (dane[1] << 4));
                }else if( type == 3){
                    mCurAddr = (UInt32)((dane[0] << (8+4)) | (dane[1] << 4));
                }else if( type == 4){
                    mCurAddr = (UInt32)((dane[0] << (8+16)) | (dane[1] << 16));
                }else if( type == 5){
                    mCurAddr = (UInt32)((dane[0] << (8 + 16)) | (dane[1] << 16));
                }

                    return null;
            }
        }
        
        public byte[] lineToArray(int index)
        {
            string str = mHexLines[index];
            int cnt = str.Length;

            if ((cnt & 0x01) == 0)
                throw new System.ArgumentException("Parzysta liczba znakow w linii HEX: " + index.ToString());


            byte[] v = new byte[cnt / 2];

            for (int i = 1; i < cnt; i += 2)
            {
                string str2 = str.Substring(i, 2);
                int ind = i / 2;
                v[ind] = byte.Parse(str2, System.Globalization.NumberStyles.HexNumber);
            }

            return v;
        }

        public byte[] lineToArray(string str)
        {
            int cnt = str.Length;

            if ((cnt & 0x01) != 0)
                throw new System.ArgumentException("Parzysta liczba znakow w linii HEX: ");

            byte[] v = new byte[cnt / 2];

            for (int i = 0; i < cnt; i += 2)
            {
                string str2 = str.Substring(i, 2);
                int ind = i / 2;
                v[ind] = byte.Parse(str2, System.Globalization.NumberStyles.HexNumber);
            }

            return v;
        }
        
        public byte[] readAddr6B(UInt32 addr, ref MDataPacket data)
        {

            data = null;
            // przejdz przez wszystkie adresy
            // sprawdz czy adres w zasiegu linii

            int cnt = mlDataPackets.Count;
            for( int i=0; i<cnt; i++)
            {
                MDataPacket packet = mlDataPackets[i];

                if( addr == packet.mAddr )
                {
                    data = packet;
                    return packet.mData;

                }

            }

            return null;
        }
        
        public void saveFile(string fileName) 
        {
            string fileStr = mHexLines[0] + "\r\n";

            int cnt = mlDataPackets.Count;
            for( int i= 0; i<cnt; i++ ) 
            {
                MDataPacket packet = mlDataPackets[i];

                fileStr += packet.genStr() + "\r\n";

            }

            int cntHex = mHexLines.Length;
            fileStr += mHexLines[cntHex - 2] + "\r\n";
            fileStr += mHexLines[cntHex - 1] + "\r\n";

            System.IO.File.WriteAllText( fileName, fileStr );
            System.Diagnostics.Process.Start( "notepad.exe", fileName );
        }
    }
}

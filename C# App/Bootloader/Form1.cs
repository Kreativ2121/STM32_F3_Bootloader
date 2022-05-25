using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;

namespace Bootloader
{
    public partial class Form1 : Form
    {
        MHexParser mHexParser = null;               // Instancja odpowiadająca za parsowanie pliku i wysyłanie ramek.

        public static bool mIsToRedraw = false;     // Flaga wymuszająca przerysowanie GUI.
        public static string mConsoleText = "";     // Zawartość konsoli.

        public enum Mode : int  // Tryb w którym obecnie się znajdujemy.
        {
            Start = 0,
            Upload = 1,
            Finish = 2,
            Error = 3
        }
        public static Mode mMode = Mode.Start;

        public Form1()  // Konstruktor.
        {
            InitializeComponent();

            mHexParser = new MHexParser(mvCOM);

            // Wczytaj ostatnio używany plik.hex
            try
            {
                string file = System.IO.File.ReadAllText("LastUsedFile.txt");
                char[] delims = new[] { '\r', '\n' };
                file = file.Split(delims, System.StringSplitOptions.RemoveEmptyEntries)[0];

                mHexParser.parseFile(file);

                mvTextFilePath.Text = file;

                mConsoleText += "Poprawnie wczytano ostatni plik .hex \r\n";
                mIsToRedraw = true;
            }
            catch
            {
                //MessageBox.Show("Coś poszło nie tak");
            }
        }

        private void mvReadFile_Click(object sender, EventArgs e)   // Wczytaj i sparsuj plik .hex.
        {
            // Pokaż okno z wyborem pliku i pobierz wynik.
            DialogResult result = mvFileBrowser.ShowDialog();

            if (result == DialogResult.OK) // Sprawdź czy poprawny.
            {
                mvTextFilePath.Text = mvFileBrowser.FileName;

                mHexParser.parseFile(mvFileBrowser.FileName);

                mConsoleText += "Poprawnie wczytano plik .hex \r\n";
                mIsToRedraw = true;

                // Zapisz ostatnio używany plik - do szybszego uruchomienia następnym razem.
                using (StreamWriter outputFile = new StreamWriter("LastUsedFile.txt"))
                {
                    outputFile.WriteLine(mvFileBrowser.FileName);
                }
            }
        }

        private void mvButUploadBootloader_Click(object sender, EventArgs e)    // Otwórz port i rozpocznij wysyłanie programu.
        {
            try
            {
                mvCOM.Open();
            }
            catch
            {
                MessageBox.Show("Nieprawidłowy port COM!");
                mvTimerFrame.Enabled = false;

                return;
            }

            mvTimerFrame.Enabled = true;
        }

        private void mvButRunProgram_Click(object sender, EventArgs e)  // Wyślij ramkę rozpoczynającą wykonanie wysłanego programu.
        {
            mHexParser.sendFrame_AppStart();
        }

        private void mvButTest_Click(object sender, EventArgs e)    // Testowy button.
        {
            mHexParser.sendFrame_WriteFlash();
        }

        private void mvButRefresh_Click(object sender, EventArgs e)
        {
            mHexParser.parseFile(mvTextFilePath.Text);

            mConsoleText += "Odświeżono zawartość pliku .hex\r\n";
            mIsToRedraw = true;
        }

        private void mvTimerGUI_Tick(object sender, EventArgs e)    // Timer aktualizujący GUI.
        {
            if (mIsToRedraw)
            {
                mvConsole.Text = mConsoleText;

                // Autoscroll
                mvConsole.SelectionStart = mvConsole.Text.Length - 1;
                mvConsole.ScrollToCaret();

                mIsToRedraw = false;
            }
        }

        private void mvTimerFrame_Tick(object sender, EventArgs e)  // Timer wymuszający wysyłanie kolejnych ramek z programem.
        {
            switch(mMode)   // Wybierz obecny tryb.
            {
                case Mode.Start:    // Wysłanie ramki rozpoczynającej.
                    mHexParser.sendFrame_AppStart();
                    mMode = Mode.Upload;

                    break;


                case Mode.Upload:   // Wysłanie całego programu.
                    if (mHexParser.mIsAnsReceived)  // Sprawdź czy poprzednia wiadomość została poprawnie wysłana i otrzymaliśmy odpowiedź.
                    {
                        if (mHexParser.mdataSentCnt == mHexParser.mlDataPackets.Count) // Wysłaliśmy wszystko, przejdź do następnej części.
                        {
                            mMode = Mode.Finish;
                        }
                        else    // Coś jeszcze można wysłać.
                        {
                            mHexParser.sendFrame_WriteFlash();
                        }
                        
                    }
                    else    // Błąd lub brak odpowiedzi.
                    {
                        mMode = Mode.Error;
                    }

                    break;


                case Mode.Finish:   // Wysłanie ramki zakańczającej.
                    mHexParser.sendFrame_BootloaderProgOk();

                    break;

                        
                case Mode.Error:    // Gdzieś wystąpił problem.
                    mConsoleText += "Napotkano błąd, przerywam operację";
                    mIsToRedraw = true;

                    mvTimerFrame.Enabled = false;
                    mMode = Mode.Start;

                    mHexParser.sendFrame_BootloaderStop();

                    break;
            }
        }

        private void mvCOM_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)   // Wywoływana przy odebraniu danych przez port szeregowy.
        {
            byte[] tab = { };

            try
            {
                while (mvCOM.ReadBufferSize > 0)    // Przepisz wszystkie odebrane dane do tablicy.
                {
                    tab[tab.Length] = (byte)mvCOM.ReadByte();
                }

                switch(tab[MHexParser.FRAME_POS_TYPE])  // Sprawdź typ ramki.
                {
                    case MHexParser.FRAME_TYPE_ReadFlash:   // Ramka ReadFlash.
                        mHexParser.readFrame_ReadFlash(tab);    // Zinterpretuj ramkę.

                        break;

                    default:    // Nieobsługiwana ramka.
                        MessageBox.Show("Niepoprawny typ ramki: " + tab[MHexParser.FRAME_POS_TYPE]);
                        mMode = Mode.Error;

                        break;
                }
            }
            catch
            {
                MessageBox.Show("Napotkano błąd przy odczycie odebranych danych.");
                mMode = Mode.Error;
            }
        }
    }
}

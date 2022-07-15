namespace Bootloader
{
    partial class Form1
    {
        /// <summary>
        /// Wymagana zmienna projektanta.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Wyczyść wszystkie używane zasoby.
        /// </summary>
        /// <param name="disposing">prawda, jeżeli zarządzane zasoby powinny zostać zlikwidowane; Fałsz w przeciwnym wypadku.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kod generowany przez Projektanta formularzy systemu Windows

        /// <summary>
        /// Metoda wymagana do obsługi projektanta — nie należy modyfikować
        /// jej zawartości w edytorze kodu.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.mvFileBrowser = new System.Windows.Forms.OpenFileDialog();
            this.mvReadFile = new System.Windows.Forms.Button();
            this.mvTextFilePath = new System.Windows.Forms.TextBox();
            this.mvButUploadBootloader = new System.Windows.Forms.Button();
            this.mvButRunProgram = new System.Windows.Forms.Button();
            this.mvConsole = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.mvTimerGUI = new System.Windows.Forms.Timer(this.components);
            this.mvTimerFrame = new System.Windows.Forms.Timer(this.components);
            this.mvCOM = new System.IO.Ports.SerialPort(this.components);
            this.mvButTest = new System.Windows.Forms.Button();
            this.mvButRefresh = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // mvFileBrowser
            // 
            this.mvFileBrowser.DefaultExt = "hex";
            this.mvFileBrowser.Filter = "Plik hex (*.hex)|*.hex|Wszystkie pliki (*.*)|*.*";
            this.mvFileBrowser.Title = "Wybierz plik .hex";
            // 
            // mvReadFile
            // 
            this.mvReadFile.Location = new System.Drawing.Point(481, 5);
            this.mvReadFile.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.mvReadFile.Name = "mvReadFile";
            this.mvReadFile.Size = new System.Drawing.Size(99, 31);
            this.mvReadFile.TabIndex = 0;
            this.mvReadFile.Text = "Otwórz";
            this.mvReadFile.UseVisualStyleBackColor = true;
            this.mvReadFile.Click += new System.EventHandler(this.mvReadFile_Click);
            // 
            // mvTextFilePath
            // 
            this.mvTextFilePath.Location = new System.Drawing.Point(11, 10);
            this.mvTextFilePath.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.mvTextFilePath.Name = "mvTextFilePath";
            this.mvTextFilePath.Size = new System.Drawing.Size(465, 22);
            this.mvTextFilePath.TabIndex = 1;
            this.mvTextFilePath.WordWrap = false;
            // 
            // mvButUploadBootloader
            // 
            this.mvButUploadBootloader.Location = new System.Drawing.Point(11, 72);
            this.mvButUploadBootloader.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.mvButUploadBootloader.Name = "mvButUploadBootloader";
            this.mvButUploadBootloader.Size = new System.Drawing.Size(227, 61);
            this.mvButUploadBootloader.TabIndex = 2;
            this.mvButUploadBootloader.Text = "Wgraj bootloader";
            this.mvButUploadBootloader.UseVisualStyleBackColor = true;
            this.mvButUploadBootloader.Click += new System.EventHandler(this.mvButUploadBootloader_Click);
            // 
            // mvButRunProgram
            // 
            this.mvButRunProgram.Location = new System.Drawing.Point(243, 72);
            this.mvButRunProgram.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.mvButRunProgram.Name = "mvButRunProgram";
            this.mvButRunProgram.Size = new System.Drawing.Size(227, 61);
            this.mvButRunProgram.TabIndex = 3;
            this.mvButRunProgram.Text = "Uruchom program";
            this.mvButRunProgram.UseVisualStyleBackColor = true;
            this.mvButRunProgram.Click += new System.EventHandler(this.mvButRunProgram_Click);
            // 
            // mvConsole
            // 
            this.mvConsole.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.mvConsole.Font = new System.Drawing.Font("Consolas", 10F);
            this.mvConsole.Location = new System.Drawing.Point(11, 170);
            this.mvConsole.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.mvConsole.Name = "mvConsole";
            this.mvConsole.ReadOnly = true;
            this.mvConsole.Size = new System.Drawing.Size(707, 477);
            this.mvConsole.TabIndex = 4;
            this.mvConsole.Text = "";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 150);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "Konsola";
            // 
            // mvTimerGUI
            // 
            this.mvTimerGUI.Enabled = true;
            this.mvTimerGUI.Tick += new System.EventHandler(this.mvTimerGUI_Tick);
            // 
            // mvTimerFrame
            // 
            this.mvTimerFrame.Interval = 300;
            this.mvTimerFrame.Tick += new System.EventHandler(this.mvTimerFrame_Tick);
            // 
            // mvCOM
            // 
            this.mvCOM.BaudRate = 38400;
            this.mvCOM.PortName = "COM6";
            this.mvCOM.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.mvCOM_DataReceived);
            // 
            // mvButTest
            // 
            this.mvButTest.Location = new System.Drawing.Point(623, 72);
            this.mvButTest.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.mvButTest.Name = "mvButTest";
            this.mvButTest.Size = new System.Drawing.Size(95, 61);
            this.mvButTest.TabIndex = 6;
            this.mvButTest.Text = "Test";
            this.mvButTest.UseVisualStyleBackColor = true;
            this.mvButTest.Click += new System.EventHandler(this.mvButTest_Click);
            // 
            // mvButRefresh
            // 
            this.mvButRefresh.Location = new System.Drawing.Point(585, 5);
            this.mvButRefresh.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.mvButRefresh.Name = "mvButRefresh";
            this.mvButRefresh.Size = new System.Drawing.Size(138, 31);
            this.mvButRefresh.TabIndex = 7;
            this.mvButRefresh.Text = "Wczytaj ponownie";
            this.mvButRefresh.UseVisualStyleBackColor = true;
            this.mvButRefresh.Click += new System.EventHandler(this.mvButRefresh_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(730, 658);
            this.Controls.Add(this.mvButRefresh);
            this.Controls.Add(this.mvButTest);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.mvConsole);
            this.Controls.Add(this.mvButRunProgram);
            this.Controls.Add(this.mvButUploadBootloader);
            this.Controls.Add(this.mvTextFilePath);
            this.Controls.Add(this.mvReadFile);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Bootloader Uploader";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button mvReadFile;
        public System.Windows.Forms.OpenFileDialog mvFileBrowser;
        public System.Windows.Forms.TextBox mvTextFilePath;
        private System.Windows.Forms.Button mvButUploadBootloader;
        private System.Windows.Forms.Button mvButRunProgram;
        private System.Windows.Forms.RichTextBox mvConsole;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Timer mvTimerGUI;
        private System.Windows.Forms.Timer mvTimerFrame;
        private System.IO.Ports.SerialPort mvCOM;
        private System.Windows.Forms.Button mvButTest;
        private System.Windows.Forms.Button mvButRefresh;
    }
}


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace EditorApp
{
    public partial class ChooseProjectForm : Form
    {
        public ChooseProjectForm()
        {
            InitializeComponent();
        }

        private void ChooseProjectForm_Load(object sender, EventArgs e)
        {
            FormBorderStyle = FormBorderStyle.FixedSingle;
        }

        //protected override void OnPaint(PaintEventArgs e)
        //{
        //    e.Graphics.TextRenderingHint = TextRenderingHint.AntiAlias;
        //    base.OnPaint(e);
        //}

        private void folderBrowserDialog1_HelpRequest(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.SelectedPath = @"C:\Users\webmo\Google Drive\Projects\VisualStudio\EngineCore\StandaloneApp";
            var res = folderBrowserDialog1.ShowDialog();
            if (res == DialogResult.OK)
            {
                string dirPath = folderBrowserDialog1.SelectedPath;
                if (!Directory.Exists(dirPath + "\\EngineData"))
                {
                    MessageBox.Show("No correct data in selected directory");
                }
                else
                {
                    using (Form1 form = new Form1(dirPath))
                    {
                        this.Hide();

                        form.Text = "Project";
                        form.FormClosed += Form2_FormClosed;

                        //form.Parent = this;

                        form.ShowDialog();
                    }
                    
                }
            }
        }


        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.Close(); // will exit the application     
        }
    }
}

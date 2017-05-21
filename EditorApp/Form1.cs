using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EditorApp
{
    public partial class Form1 : Form
    {
        [DllImport("EngineCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Init(IntPtr ptr);

        [DllImport("EngineCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Render();

        [DllImport("EngineCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReloadScene();

        [DllImport("EngineCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReloadScripts();

        [DllImport("EngineCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Tick();

        [DllImport("EngineCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Resize(int width, int height);

        public Form1()
        {
            InitializeComponent();

            Init(openGLControl1.Handle);

            openGLControl1.PaintAction += PaintAction;
            //openGLControl1.SizeChangedAction += ResizeAction;

            InitWatcher();

        }

        private void PaintAction()
        {
            if (_needsReload)
            {
                _needsReload = false;
                ReloadScripts();
            }

            Tick();
            Render();
        }

        private void ResizeAction(int w, int h)
        {
            Resize(w, h);
        }

        private FileSystemWatcher watcher;
        private void InitWatcher()
        {
            watcher = new FileSystemWatcher();
            watcher.Path = "ProjectData\\Scripts";
            /* Watch for changes in LastAccess and LastWrite times, and
               the renaming of files or directories. */
            watcher.NotifyFilter = NotifyFilters.LastWrite | NotifyFilters.FileName;
            // Only watch text files.
            watcher.Filter = "*.lua";

            // Add event handlers.
            watcher.Changed += OnChanged;

            watcher.EnableRaisingEvents = true;
        }

        private bool _needsReload = false;

        private void OnChanged(object source, FileSystemEventArgs e)
        {
            _needsReload = true;

            Console.WriteLine("File: " + e.FullPath + " " + e.ChangeType);
        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }


        private void openGLControl1_Load(object sender, EventArgs e)
        {
           
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //if (_needsReload)
            //{
            //    _needsReload = false;
            //    ReloadScripts();
            //}

            //Tick();
            //Render();
        }
    }
}

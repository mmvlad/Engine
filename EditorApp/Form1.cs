using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.Collections.Generic;

namespace EditorApp
{
    public partial class Form1 : Form
    {

        #region Dll Import

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

        [DllImport("EngineCore.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetProjectDir(string dir);

        #endregion

        private string      _projectdir;
        private Scene       _scene;
        private GameObject  _currentObj;

        private bool _isSimulating = false;

        public Form1(string projectDir)
        {
            _projectdir = projectDir;

            InitializeComponent();
            listView1.View = View.List;

            SetProjectDir(projectDir);
            Init(openGLControl1.Handle);

            openGLControl1.PaintAction += PaintAction;
            openGLControl1.SizeChangedAction += ResizeAction;

            this.textBox1.KeyPress += TextBoxKeyPress;
            this.textBox2.KeyPress += TextBoxKeyPress;
            this.textBox3.KeyPress += TextBoxKeyPress;


            InitWatcher();

            LoadSceneElements();
        }

        private void TextBoxKeyPress(object sender, KeyPressEventArgs e)
        {
            if (_currentObj == null)
            {
                e.Handled = true;
                return;
            }

            ValidateFloatInput(sender, e);
        }

        public void ValidateFloatInput(object sender, KeyPressEventArgs e)
        {
            if (!(char.IsDigit(e.KeyChar) || e.KeyChar == (char) Keys.Back || e.KeyChar == '.'))
            {
                e.Handled = true;
            }

            TextBox txtDecimal = sender as TextBox;

            if (e.KeyChar == '.' && txtDecimal.Text.Contains("."))
            {
                e.Handled = true;
            }
        }

        private void LoadSceneElements()
        {
            var path = _projectdir + "\\ProjectData\\Scenes\\MainScene.json";
            var sceneStr = File.ReadAllText(path);
            //Console.WriteLine("Text read: " + sceneStr);
            

            _scene = SceneJsonConverter.ParseStr(sceneStr);
            Console.WriteLine("Loaded scene: "  + _scene);

            foreach (var sceneObject in _scene.Objects)
            {
                listView1.Items.Add(sceneObject.Name);
            }

        }

        private void PaintAction()
        {
            if (_needsReload)
            {
                _needsReload = false;
                ReloadScripts();
            }

            if (_isSimulating)
            {
                Tick();
            }
            
            Render();
        }

        private void ResizeAction(int w, int h)
        {
            Resize(w, h);
        }

        #region Script monitor change

        private FileSystemWatcher watcher;
        private void InitWatcher()
        {
            watcher = new FileSystemWatcher();
            watcher.Path = _projectdir + "\\ProjectData\\Scripts";
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

        #endregion

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {
        }

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {
        }


        private void openGLControl1_Load(object sender, EventArgs e)
        { 
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            FormBorderStyle = FormBorderStyle.FixedSingle;
        }


        private void listView1_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            if (listView1.SelectedIndices.Count > 0)
            {
                int i = listView1.SelectedIndices[0];
                _currentObj = _scene.Objects[i];

                this.textBox1.Text = _currentObj.Position.X.ToString();
                this.textBox2.Text = _currentObj.Position.Y.ToString();
                this.textBox3.Text = _currentObj.Position.Z.ToString();
            }
            else
            {
                _currentObj = null;
                this.textBox1.Text = "";
                this.textBox2.Text = "";
                this.textBox3.Text = "";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            _isSimulating = true;
        }

        private void stopBtn_Click(object sender, EventArgs e)
        {
            _isSimulating = false;
        }

        private void label1_Click(object sender, EventArgs e)
        {
            
        }

        //X
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (_currentObj != null)
            {
                _currentObj.Position.X = float.Parse(textBox1.Text);
                SaveAndReloadScene();
            }
        }

        //Y
        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            if (_currentObj != null)
            {
                _currentObj.Position.Y = float.Parse(textBox2.Text);
                SaveAndReloadScene();
            }
        }

        //Z
        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            if (_currentObj != null)
            {
                _currentObj.Position.Z = float.Parse(textBox3.Text);
                SaveAndReloadScene();
            }
        }

        private void SaveAndReloadScene()
        {
            // serialize scene
            var str = SceneJsonConverter.SerializeScene(_scene);
            Console.WriteLine(str);

            var path = _projectdir + "\\ProjectData\\Scenes\\MainScene.json";
            File.WriteAllText(path, str);

            _isSimulating = false;
            ReloadScene();
        }
    }
}

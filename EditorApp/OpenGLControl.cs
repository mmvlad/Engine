using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace EditorApp
{
    
    public partial class OpenGLControl : UserControl, ISupportInitialize
    {
        public Action PaintAction { get; set; }
        public Action<int, int> SizeChangedAction { get; set; }

        private readonly Timer timerDrawing = new Timer();

        public OpenGLControl()
        {
            InitializeComponent();

            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, false);
        }

        private void timerDrawing_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }

      
        protected override void OnPaintBackground(PaintEventArgs e)
        {
           
        }

        private void OpenGLControl_Load(object sender, EventArgs e)
        {
            
        }

        public void BeginInit()
        {
            
        }

        public void EndInit()
        {
            if (!DesignMode)
            {
                timerDrawing.Interval = (int)(1000.0 / 60);
                timerDrawing.Tick += timerDrawing_Tick;

                timerDrawing.Enabled = true;
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Render(e.Graphics);
        }

        protected void Render(Graphics graphics)
        {
            if (!DesignMode && PaintAction != null)
            {
                PaintAction();
            }
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);

            if (!DesignMode && SizeChangedAction != null)
            {
                SizeChangedAction(Width, Height);
            }
        }


        protected override CreateParams CreateParams
        {
            get
            {
                int VREDRAW = 0x00000001;
                int HREDRAW = 0x00000002;
                int OWNDC = 0x00000020;
                int CHILD = 0x40000000;
                int CLIPCHILDREN = 0x02000000;
                int CLIPSIBLINGS = 0x0400000;

                CreateParams cp = base.CreateParams;
                //cp.ClassStyle |= VREDRAW | HREDRAW | OWNDC;
                //cp.ExStyle |= 0x02000000;
                cp.ClassStyle |= VREDRAW | HREDRAW | OWNDC;
                
                //cp.Style|= CLIPCHILDREN|CLIPSIBLINGS| CHILD;
                return cp;
            }
        }

    }
}

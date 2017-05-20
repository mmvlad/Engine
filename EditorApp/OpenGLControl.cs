using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EditorApp
{
    
    public partial class OpenGLControl : UserControl
    {
        public OpenGLControl()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.Opaque | ControlStyles.ResizeRedraw | ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);

            InitializeComponent();
        }

        protected override CreateParams CreateParams
        {
            get
            {
                int VREDRAW = 0x00000001;
                int HREDRAW = 0x00000002;
                int OWNDC = 0x00000020;

                CreateParams cp = base.CreateParams;
                cp.ClassStyle = VREDRAW | HREDRAW | OWNDC;
                cp.ExStyle |= 0x02000000;
                // maybe cp.Style|=WS.CLIPCHILDREN|WS.CLIPSIBLINGS;
                return cp;
            }
        }

        private void OpenGLControl_Load(object sender, EventArgs e)
        {
            
        }
    }
}

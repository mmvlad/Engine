using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EditorApp
{
    public class Engine
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

        public void InitEngine(IntPtr ptr)
        {
            Init(ptr);
        }

        public void RenderCanvas()
        {
            Render();
        }

        public void LoadScene()
        {
            ReloadScene();
        }

        public void LoadScripts()
        {
            ReloadScripts();
        }

        public void ExecuteScripts()
        {
            Tick();
        }

        public void ResizeWindow(int w, int h)
        {
            Resize(w, h);
        }
    }
}

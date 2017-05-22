using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace EditorApp
{
    public class Scene
    {
        [JsonProperty("objects")]
        public List<GameObject> Objects { get; set; }

        public Scene()
        {
            Objects = new List<GameObject>();
        }

        public override string ToString()
        {
            string res = "Objects: ";
            foreach (var gameObject in Objects)
            {
                res += "\n" + gameObject.ToString();
            }

            return res;
        }
    }
}

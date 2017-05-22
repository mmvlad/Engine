using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace EditorApp
{
    [System.Serializable]
    public class Vector3
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }

        public override string ToString()
        {
            return "x: " + X + ", y: " + Y + ", z: " + Z;
        }
    }

    public class GameObject
    {
        public GameObject()
        {
            Scripts = new List<string>();
        }

        [JsonProperty("name")]
        public string Name { get; set; }

        [JsonProperty("mesh")]
        public string Mesh { get; set; }

        [JsonProperty("material")]
        public string Material { get; set; }

        [JsonProperty("layer")]
        public string Layer { get; set; }

        [JsonProperty("position")]
        public Vector3 Position { get; set; }

        [JsonProperty("scale")]
        public Vector3 Scale { get; set; }

        [JsonProperty("rotation")]
        public Vector3 Rotation { get; set; }

        [JsonProperty("scripts")]
        public List<string> Scripts { get; set; }

        public override string ToString()
        {
            string res = "Name: " + Name + ", Mesh name: " + Mesh + ", Material: " + Material
                         + ", Layer: " + Layer + ", Position: " + Position + "Scripts: ";
            foreach (var scriptName in Scripts)
            {
                res += scriptName + ", ";
            }
            res += " end.";

            return res;
        }
    }
}

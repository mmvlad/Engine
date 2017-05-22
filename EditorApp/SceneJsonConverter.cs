using Newtonsoft.Json.Linq;
using System.Linq;

namespace EditorApp
{
    public class SceneJsonConverter
    {
        public static Scene ParseStr(string jsonStr)
        {
            Scene scene = new Scene();

            var jsonObj = JObject.Parse(jsonStr);

            var objects = jsonObj["objects"];

            foreach (var obj in objects)
            {
                GameObject g = new GameObject();

                g.Name      = (string)obj["name"];
                g.Mesh      = (string)obj["mesh"];
                g.Material  = (string)obj["material"];
                g.Layer     = (string)obj["layer"];

                g.Position = ParseVector((string) obj["position"]);
                g.Scale = ParseVector((string)obj["scale"]);
                g.Rotation = ParseVector((string)obj["rotation"]);

                var scripts = obj["scripts"];

                foreach (var script in scripts)
                {
                    g.Scripts.Add((string)script);
                }

                scene.Objects.Add(g);
            }       
                     
            return scene;
        }

        public static Vector3 ParseVector(string str)
        {
            Vector3 res = new Vector3();

            var parts = str.Split(',');

            res.X = float.Parse(parts[0]);
            res.Y = float.Parse(parts[1]);
            res.Z = float.Parse(parts[2]);

            return res;
        }

        public static string VectorToStr(Vector3 vec)
        {
            return vec.X.ToString("0.00") + "," + vec.Y.ToString("0.00") + "," + vec.Z.ToString("0.00");
        }

        public static string SerializeScene(Scene scene)
        {
            JObject res = new JObject(
                new JProperty("objects", new JArray(
                    from obj in scene.Objects
                    select new JObject(
                        new JProperty("name", obj.Name),
                        new JProperty("mesh", obj.Mesh),
                        new JProperty("material", obj.Material),
                        new JProperty("layer", obj.Layer),
                        new JProperty("position", VectorToStr(obj.Position)),
                        new JProperty("scale", VectorToStr(obj.Scale)),
                        new JProperty("rotation", VectorToStr(obj.Rotation)),
                        new JProperty("scripts", new JArray(from script in obj.Scripts select new JValue(script)))
                        )
                    )));


            return res.ToString();
        }
    }
}

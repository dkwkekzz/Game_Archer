using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Json;
using System.Web.Script.Serialization;
using System.IO;

namespace project_gdi_
{
    public class JsonBuilder
    {
        //static StreamWriter writer;
        public JsonBuilder()
        { 

        }

        static public void CreateInitJsonData(string[] properties, string destFolder)
        {
            JsonObjectCollection json = new JsonObjectCollection();
            
            string[] names = { "beats", "subtitleText", "startTime", "endTime", "songCounter", "subtitleGroup", "beatCounter" };
            for (var i = 0; i < names.Length; i++)
            {
                json.Add(new JsonStringValue(names[i], properties[i].Replace("\r\n", "").Replace("\t", "")));
                //ret += GetJsonString(json, names[i]);
            }
            
            var ret = "var initProperties = '" + new JavaScriptSerializer().Serialize(json) + "';\n";

            System.IO.File.WriteAllText(destFolder + "/jsonData.js", ret);

        }

        static public void CreateOutputJsonData(string data, string destFolder)
        {
            //var ret = "var output = '" + data;
            //WriteJsonFile(data, destFolder + "/jsonData.js");

            System.IO.File.AppendAllText(destFolder + "/jsonData.js", data);

        }

        //destFolder + "/jsonData.js"
        static private void WriteJsonFile(string data, string fileName)
        {
            //if(writer == null)
            //{
            //    writer = new StreamWriter(fileName);
            //}
            //json 파일 쓰기
            try
            {
                System.IO.File.AppendAllText(fileName, data);
                //writer.WriteLine(data);
            }
            catch (Exception e)
            {
                //writer.Close();
                throw e;
            }
        }
        
        private string GetJsonString(JsonObjectCollection col, string field)
        {
            try
            {
                return Convert.ToString(col[field].GetValue());
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format(" {0} : [ {1} ] ", ex.Message, field));
            }

        }

    }
}

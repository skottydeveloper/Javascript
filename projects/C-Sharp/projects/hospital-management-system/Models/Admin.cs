using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment_1.Models
{
    public class Admin
    {
        // Properties for the Admin class.
        public int ID { get; set; }
        public string Name { get; set; }
        public string Password { get; set; }

        // Constructor to initialise the Admin object.
        public Admin(int id, string name, string password)
        {
            ID = id;
            Name = name;
            Password = password;
        }

        // Override ToString to provide a string representation of the Admin object.
        public override string ToString()
        {
            return $"Admin Name: {Name}";
        }
    }
}

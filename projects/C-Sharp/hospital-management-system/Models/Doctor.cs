using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment_1.Models
{
    public class Doctor
    {
        // Properties for the Doctor class.
        public int ID { get; set; }
        public string Name { get; set; }
        public string Password { get; set; }

        // Constructor to initialise the Doctor object.
        public Doctor(int id, string name, string password)
        {
            ID = id;
            Name = name;
            Password = password;
        }

        // Override ToString to provide a string representation of the Doctor object.
        public override string ToString()
        {
            return $"Doctor Name: {Name}, ID: {ID}";
        }
    }
}

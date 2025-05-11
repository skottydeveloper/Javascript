using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment_1.Models
{
    public class Patient
    {
        // Properties for the Patient class.
        public int ID { get; set; }
        public string Name { get; set; }
        public string Password { get; set; }
        public Doctor AssignedDoctor { get; set; }

        // Constructor to initialise the Patient object.
        public Patient(int id, string name, string password, Doctor assignedDoctor = null)
        {
            ID = id;
            Name = name;
            Password = password;
            AssignedDoctor = assignedDoctor;
        }

        // Override ToString to provide a string representation of the Patient object.
        public override string ToString()
        {
            string doctorName = AssignedDoctor != null ? AssignedDoctor.Name : "None";
            return $"Patient Name: {Name}, ID: {ID}, Assigned Doctor: {doctorName}";
        }
    }
}

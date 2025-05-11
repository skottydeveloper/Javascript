using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assignment_1.Models
{
    public class Appointment
    {
        // Properties for the Appointment class.
        public Doctor Doctor { get; set; }
        public Patient Patient { get; set; }

        // Constructor to initialise the Appointment object.
        public Appointment(Doctor doctor, Patient patient)
        {
            Doctor = doctor;
            Patient = patient;
        }

        // Override ToString to provide a string representation of the Appointment object.
        public override string ToString()
        {
            return $"Appointment: Doctor {Doctor.Name}, Patient {Patient.Name}";
        }
    }
}

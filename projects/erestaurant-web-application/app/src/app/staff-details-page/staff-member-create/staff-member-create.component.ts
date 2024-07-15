import { Component } from "@angular/core";
import { NgForm, FormControl, Validators } from "@angular/forms"

import { StaffService } from "../staff.service";

@Component({
  selector: 'app-staff-create',
  templateUrl: './staff-member-create.component.html',
  styleUrls: ['./staff-member-create.component.css']
})
export class StaffCreateComponent {
  enteredName = "";
  enteredRole = "";
  enteredEmail = "";
  enteredPhone = null;

  email = new FormControl('', [Validators.required, Validators.email]);

  constructor(public staffService: StaffService) {}

  onAddStaff(form: NgForm) {
    if(form.invalid) {
      return;
    }
    console.log("added staff");
    this.staffService.addStaff(form.value.enteredName,
      form.value.enteredRole,
      form.value.enteredEmail,
      form.value.enteredPhone);
  }
  getErrorMessage() {
    if (this.email.hasError('required')) {
      return 'You must enter an email';
    }

    return this.email.hasError('email') ? 'Not a valid email' : '';
  }
}

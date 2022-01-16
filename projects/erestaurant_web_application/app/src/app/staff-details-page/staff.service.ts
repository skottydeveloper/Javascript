import { Injectable } from "@angular/core";
import { Subject } from 'rxjs';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';


import { Staff } from './staff.model';

@Injectable({providedIn: 'root'})

export class StaffService {
  private staffs: Staff[] = [];
  private staffUpdated = new Subject<Staff[]>();

  getStaff() {
    return [...this.staffs];
  }

  getStaffUpdateListener() {
    return this.staffUpdated.asObservable();
  }


  addStaff(name: string, role: string, email: string, phone: number) {
    const staff: Staff = {name: name, role: role, email: email, phone: phone}
    this.staffs.push(staff);
    this.staffUpdated.next([...this.staffs])
    }
  /*deleteStaff(staffs: Staff[] ) {
    this.staffs = splice()
  }*/
}



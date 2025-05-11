import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';

import { Staff } from '../staff.model';
import { StaffService} from '../staff.service';

@Component({
  selector: 'app-staff-list',
  templateUrl: './staff-member-list.component.html',
  styleUrls: ['./staff-member-list.component.css']
})
export class StaffListComponent implements OnInit, OnDestroy {

  staffs: Staff[] = [];
  currentStaff: Staff[] = this.staffService.getStaff();
  private staffSub: Subscription;

  constructor(public staffService: StaffService) {}

  ngOnInit() {
    this.staffs = this.staffService.getStaff();
    this.staffSub = this.staffService.getStaffUpdateListener().subscribe((staffs: Staff[]) => {
      this.staffs = staffs;
    });

  }

  ngOnDestroy() {
    this.staffSub.unsubscribe();
  }

  delete(size) {
    this.staffs.splice(size, 1)
  }
  /*delete() {
    this.currentStaff = this.staffService.getStaff();
    //'Are you sure you want to delete' +
    alert(this.currentStaff.name.toString());
  }*/
}



//sorted by role, sorted alphabetically
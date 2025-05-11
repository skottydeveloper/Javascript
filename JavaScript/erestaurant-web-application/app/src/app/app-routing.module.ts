import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { MenuDetailComponent } from './menu-detail/menu-detail.component';
import { MenuListComponent } from './menu-list/menu-list.component';
import { ReservationListComponent } from './reservation-list/reservation-list.component';
import { ReservationComponent } from './reservation/reservation.component';
import { StaffCreateComponent } from './staff-details-page/staff-member-create/staff-member-create.component';

import { StaffListComponent } from './staff-details-page/staff-member-list/staff-member-list.component';
import { StaffComponent } from './staff-details-page/staff.component';


const routes: Routes = [
  {
    path: '',
    component: HomeComponent,
  },
  {
    path: 'reservation',
    component: ReservationComponent,
  },
  {
    path: 'reservation-list',
    component: ReservationListComponent,
  },
  {
    path: 'menu',
    component: MenuListComponent,
  },
  {
    path: 'staff',
    component: StaffComponent,
  },
  {
    path: 'menu/:id',
    component: MenuDetailComponent,
  },

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }

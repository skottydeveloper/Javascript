import { Component, OnInit } from '@angular/core';
import { ReservationService } from '../reservations.service';
import { Menu } from '../Menu';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-menu-detail',
  templateUrl: './menu-detail.component.html',
  styleUrls: ['./menu-detail.component.css']
})
export class MenuDetailComponent implements OnInit {

  public menu: Menu;
  public error: string;
  public loading = true;
  constructor(
    private route: ActivatedRoute,
    private reservationService: ReservationService,
  ) { }

  ngOnInit(): void {
    const id = this.route.snapshot.paramMap.get('id');
    this.reservationService.getMenu(id)
      .subscribe((menu: Menu) => {
        this.menu = menu;
        this.loading = false;
      },
      (error) => {
        this.error = error.message;
        this.loading = false;
      }
      );
  }
}

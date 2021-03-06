Action()
{ 
	lr_start_transaction("UC06_SearchTicket");
	
	homePage();
	
	login();

	lr_start_transaction("clickToFlights");
	
	web_reg_find("Text=Find Flight",LAST);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("clickToFlights",LR_AUTO);

	lr_start_transaction("searchTicket");
	
/*Correlation comment - Do not change!  Original value='020;338;06/25/2022' Name ='outboundFlight_1' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Ordinal=ALL",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
		
	web_reg_find("Text/IC=<blockquote>Flight departing from <B>{Town}</B> to <B>{Town2}</B> on <B>{DepartDate}</B>",LAST);
		
	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={Town}", ENDITEM, 
		"Name=departDate", "Value={DepartDate}", ENDITEM, 
		"Name=arrive", "Value={Town2}", ENDITEM, 
		"Name=returnDate", "Value={ReturnDate}", ENDITEM, 
		"Name=numPassengers", "Value={NumPassengers}", ENDITEM, 
		"Name=seatPref", "Value={SeatingPreference}", ENDITEM, 
		"Name=seatType", "Value={TypeOfSeat}", ENDITEM, 
		"Name=.cgifields", "Value={TypeOfSeat}", ENDITEM, 
		"Name=.cgifields", "Value={SeatingPreference}", ENDITEM, 
		"Name=findFlights.x", "Value=38", ENDITEM, 
		"Name=findFlights.y", "Value=6", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);
		         
 	lr_end_transaction("searchTicket",LR_AUTO);
	
	lr_start_transaction("departureTime");
	
	web_reg_find("Text=Flight Reservation",LAST);

	lr_save_string(lr_eval_string(lr_paramarr_random("outboundFlight")),"outboundFlightVal");
	
	web_submit_data("reservations.pl_2",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t17.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={outboundFlightVal}", ENDITEM,
		"Name=numPassengers", "Value={NumPassengers}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={TypeOfSeat}", ENDITEM,
		"Name=seatPref", "Value={SeatingPreference}", ENDITEM,
		"Name=reserveFlights.x", "Value=47", ENDITEM,
		"Name=reserveFlights.y", "Value=12", ENDITEM,
		LAST);
	
	lr_end_transaction("departureTime",LR_AUTO);
			
	lr_end_transaction("UC06_SearchTicket",LR_AUTO);

	return 0;
}
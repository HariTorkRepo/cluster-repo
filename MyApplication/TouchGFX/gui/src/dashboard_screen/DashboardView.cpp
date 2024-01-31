#include <gui/dashboard_screen/DashboardView.hpp>

#include <BitmapDatabase.hpp>
#include <touchgfx/Utils.hpp>

#include <cmath>
#include <initializer_list>
#include <time.h>
#include <math.h>

// mph scale
//
//  -PI/2            0.0             PI/2
//    |               |               |
//    +---------------+---------------+
//    |               |               |
//   0.0 km/h       30.0 km/h       60.0 km/h
//
//
// mph scale
//
//  -PI/2            0.0             PI/2
//    |               |               |
//    +---------------+---------------+
//    |               |               |
//   0.0 mph        18.0 mph        36.0 mph


namespace
{
static constexpr auto PI_2 = 1.57079632679f;
static constexpr auto ticks_disable_simulation_period = 1000;
static constexpr auto battery_duration_s = 3 * 60;
static constexpr auto velocity_max_kmh = 240.0f;
static constexpr auto velocity_max_mph = 144.0f;
static constexpr auto screen_center_x = 240;
static constexpr auto screen_center_y = 240;
static constexpr auto speedometer_center_x = 240.0f;
static constexpr auto speedometer_center_y = 240.0f;
static constexpr auto outer_handle_distance_squared = 125 * 125;
}

extern volatile uint8_t SharedData[8];//speed km/hr,DTE
extern volatile uint8_t frame_102h[8];//
extern volatile uint8_t frame_103h[8];//soc bitpos : 0, no of bits = 10
extern volatile uint8_t frame_105h[8];//
extern volatile uint8_t frame_100h[8];//odo bitpos : 40, no of bits = 20


uint32_t SPORT  =  100;
uint32_t CITY  = 70;
uint32_t ECO = 50;
uint32_t ECOPlus = 35;


uint16_t soc_val = 0;

#ifndef RADTODEG
#define RADTODEG 57.295779513082320876f
#endif


void DashboardView::clamp(float& angle, float upper_limit, float lower_limit)
{
	if (angle > upper_limit)
	{
		angle = upper_limit;
	}
	else if (angle < lower_limit)
	{
		angle = lower_limit;
	}
}

void DashboardView::setupScreen()
{


	DashboardViewBase::setupScreen();

	HAL::getInstance()->setFrameRateCompensation(true);

	_battery_images[0] = &battery1;
	_battery_images[1] = &battery2;
	_battery_images[2] = &battery3;
	_battery_images[3] = &battery4;
	_battery_images[4] = &battery5;
	_battery_images[5] = &battery6;

	_current_highlight = &highlightMph;

	// init battery
	_battery._remaining_s = battery_duration_s;

	// fill graph with a bunch of values

	for (auto i = 0; i < /*graph.getMaxCapacity()*/frame_105h[4]; i++)
	{
		while (!_elevation_sim.update(1.0f))
		{
			// Update until we have a new value
		}

		graph.addDataPoint(_elevation_sim._elevation_m);
	}



	update();
}


void  DashboardView:: updateBatteryUserDefine()
{

	bool visible = 1;


	soc_val =   (((int)frame_103h[1] & 0x03) << 8) | (int)frame_103h[0];

	if(soc_val <= 16)
	{
		//1st image;

		_battery_images[0]->setVisible(visible);
		_battery_images[0]->invalidate();


		_battery_images[1]->setVisible(false);
		_battery_images[1]->invalidate();


		_battery_images[2]->setVisible(false);
		_battery_images[2]->invalidate();

		_battery_images[3]->setVisible(false);
		_battery_images[3]->invalidate();

		_battery_images[4]->setVisible(false);
		_battery_images[4]->invalidate();



		_battery_images[5]->setVisible(false);
		_battery_images[5]->invalidate();

	}
	else if(soc_val > 16 && soc_val <= 32)
	{
		//2nd image;


		_battery_images[1]->setVisible(visible);
		_battery_images[1]->invalidate();

		_battery_images[0]->setVisible(false);
		_battery_images[0]->invalidate();


		_battery_images[2]->setVisible(false);
		_battery_images[2]->invalidate();

		_battery_images[3]->setVisible(false);
		_battery_images[3]->invalidate();

		_battery_images[4]->setVisible(false);
		_battery_images[4]->invalidate();


		_battery_images[5]->setVisible(false);
		_battery_images[5]->invalidate();


	}
	else if(soc_val > 32 && soc_val <= 48)
	{
		//3rd image;


		_battery_images[2]->setVisible(visible);
		_battery_images[2]->invalidate();

		_battery_images[1]->setVisible(false);
		_battery_images[1]->invalidate();


		_battery_images[0]->setVisible(false);
		_battery_images[0]->invalidate();

		_battery_images[3]->setVisible(false);
		_battery_images[3]->invalidate();

		_battery_images[4]->setVisible(false);
		_battery_images[4]->invalidate();


		_battery_images[5]->setVisible(false);
		_battery_images[5]->invalidate();

	}
	else if(soc_val > 48 && soc_val <= 64)
	{
		//4rth image;

		_battery_images[3]->setVisible(visible);
		_battery_images[3]->invalidate();


		_battery_images[1]->setVisible(false);
		_battery_images[1]->invalidate();


		_battery_images[2]->setVisible(false);
		_battery_images[2]->invalidate();

		_battery_images[0]->setVisible(false);
		_battery_images[0]->invalidate();

		_battery_images[4]->setVisible(false);
		_battery_images[4]->invalidate();


		_battery_images[5]->setVisible(false);
		_battery_images[5]->invalidate();


	}
	else if(soc_val> 64 && soc_val <= 80)
	{
		//5th image;


		_battery_images[4]->setVisible(visible);
		_battery_images[4]->invalidate();

		_battery_images[1]->setVisible(false);
		_battery_images[1]->invalidate();


		_battery_images[2]->setVisible(false);
		_battery_images[2]->invalidate();

		_battery_images[3]->setVisible(false);
		_battery_images[3]->invalidate();

		_battery_images[0]->setVisible(false);
		_battery_images[0]->invalidate();


		_battery_images[5]->setVisible(false);
		_battery_images[5]->invalidate();


	}
	else
	{
		_battery_images[5]->setVisible(visible);
		_battery_images[5]->invalidate();


		_battery_images[1]->setVisible(false);
		_battery_images[1]->invalidate();


		_battery_images[2]->setVisible(false);
		_battery_images[2]->invalidate();

		_battery_images[3]->setVisible(false);
		_battery_images[3]->invalidate();

		_battery_images[4]->setVisible(false);
		_battery_images[4]->invalidate();

		_battery_images[4]->setVisible(false);
		_battery_images[4]->invalidate();

		_battery_images[0]->setVisible(false);
		_battery_images[0]->invalidate();


	}

	//Unicode::snprintf(remainingBuffer, 6, "%02d:%02d", minutes, seconds);

	char c = '%';
	if(soc_val>100)
	{
		soc_val = 100;
	}
	Unicode::snprintf(remainingBuffer, 6, "%d%c", soc_val, c);
	remaining.invalidate();


}

void DashboardView::updateBattery()
{
	// update battery states
	//for (auto i = 0u; i < _battery_images.size(); i++)
	for (auto i = 5; i > 0; i--)
	{

		const auto visible = (i == static_cast<uint32_t>(_battery._battery_state_step));

		if (_battery_images[i]->isVisible() != visible)
		{
			_battery_images[i]->setVisible(visible);
			_battery_images[i]->invalidate();
		}
	}

	// update remaining time
	int32_t minutes = _battery._remaining_s / 60;
	int32_t seconds = _battery._remaining_s - (minutes * 60);
	Unicode::snprintf(remainingBuffer, 6, "%02d:%02d", minutes, seconds);
	remaining.invalidate();

}


void DashboardView::updateElevation()
{
	// for the graph it makes good sense to just pass the texture values straight away, leaving them at 0..255.
	// for plausibility, since our pilot is not going from 0..255m in 2 seconds, it's probably better to scale
	// the elevation down a bit to 1/5.
	graph.addDataPoint(_elevation_sim._elevation_m);

	const bool use_meters = (_unit_length == Units::UnitLength::Meters);

	Unicode::snprintf(
			elevationLabelBuffer,
			6,
			use_meters ? "+%dm" : "+%dft",
					use_meters ? static_cast<int32_t>(_elevation_sim._elevation_m) : static_cast<int32_t>(Units::metersToFeet(_elevation_sim._elevation_m))
	);
	char watt = 'W';
	char slash = '/';
	char hour = 'h';

	Unicode::snprintf(elevationLabelBuffer, 9, "%d%c%c%c", frame_105h[4],watt,slash,hour);

	/*	string watt_val[]="W/h";
	Unicode::snprintf(elevationLabelBuffer, 6, "%d%s", frame_105h[4], watt_val);*/




	elevationLabel.invalidate();
}


void DashboardView::update()
{
	// assume constant tick speed
	const auto dt = 1.0f;
	int cnt = 0;
	++cnt;
	if (_elevation_sim.update(dt))
	{
		updateElevation();
	}

	if (_speedometer.update(dt))
	{
		updateSpeedometer(dt);
	}

	if (_battery.update(dt))
	{
		//updateBattery();
		updateBatteryUserDefine();
	}

	_tick_current++;
}

//demo code
#if 0
void DashboardView::updateSpeedometer(float dt)
{

	const auto use_kmh = (_unit_velocity == Units::UnitVelocity::KilometersPerHour);

	auto velocity_kmh = 0.0f;
	auto needle_angle = 0.0f;

	//	if (_tick_user_input_has_value && (_tick_current - _tick_user_input < ticks_disable_simulation_period))
	//	{
	//		// turn needle angle from -pi/2 .. pi/2 into a velocity from 0 to 1
	//		velocity_kmh = ((_needle_angle + PI_2) / PI) * velocity_max_kmh;
	//		_velocity_from_user_kmh = velocity_kmh;
	//		needle_angle = _needle_angle;
	//		_velocity_interpolate = 1.0f;
	//	}
	//
	//	else
	//{
	// when the simulation has expired, just linear interpolate to the value
	// the simulation is feeding to the speedometer
	velocity_kmh = (1.0f - _velocity_interpolate) *_speedometer._velocity_kmh + (_velocity_interpolate * _velocity_from_user_kmh);
	const auto velocity_normalized = use_kmh ? ((velocity_kmh / velocity_max_kmh) - 0.5f) : ((Units::kmhToMph(velocity_kmh) / velocity_max_mph) - 0.5f);
	needle_angle = velocity_normalized * PI;
	_velocity_interpolate = std::max<float>(0.0f, _velocity_interpolate - dt * 0.01f);
	//}

	// map speed from 0..60 km/h or 0..40 mph
	if (_needle_update_required || fabs(_needle_angle - needle_angle) > 0.003f)
	{
		_needle_angle = needle_angle;
		needle.invalidateContent(); // invalidate the old needle range
		needle.setZAngle(_needle_angle);
		needle.invalidateContent(); // invalidate the new needle range
		_current_highlight->updateArc(-90.0f, _needle_angle * RADTODEG);
		_needle_update_required = false;
	}

	// update displayed velocity if needed

	const auto velocity_display =  use_kmh ? velocity_kmh : Units::kmhToMph(velocity_kmh);

	const auto displayed_velocity = static_cast<int32_t>(velocity_display);
	if (displayed_velocity != _displayed_velocity)
	{
		_displayed_velocity = displayed_velocity;
		Unicode::snprintf(currentVelocityBuffer, 3, "%d", _displayed_velocity);
		currentVelocity.invalidate();
	}

	// update displayed total distance if needed
	const auto displayed_total_distance = use_kmh ? _speedometer._distance_total_km : Units::kmhToMph(_speedometer._distance_total_km);
	if (fabs(_displayed_total_distance - displayed_total_distance) > 0.05f)
	{
		_displayed_total_distance = displayed_total_distance;
		Unicode::snprintfFloat(totalDistanceBuffer, 5, "%.1f", displayed_total_distance);
		totalDistance.invalidate();
	}

}
#endif


float sineEaseInOutf(float p)
{
	return 0.5 * (1 - cos(p * M_PI));
}

double interpolate(double start, double end, double t)
{
	return start + (end - start) * t;
}

static int velocity_kmh_disp , vel_old;
static int change_active = 0;
static int velocity_to_show;
static int loop_count = 1;

float easeInOutSine(float x) {
	return -(cos(M_PI * x) - 1) / 2;
}

float easeInQuart(float x){
	return x * x * x * x;
}

float easeInOutQuint(float x){
	return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
}

float easeOutSine(float x){
	return sin((x * PI) / 2);
}

float easeInOutBack(float x) {
	const float c1 = 1.70158;
	const float c2 = c1 * 1.525;

	if (x < 0.5) {
		return (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2;
	} else {
		return (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
	}
}

float easeOutQuart(float x){
	return 1 - pow(1 - x, 4);
}

//modified

void DashboardView::updateSpeedometer(float dt)
{

	uint16_t velocityValue = (int)SharedData[3]; // speed, frame 101, bitpos : 24, no bo bits: 8
	uint8_t driveMode = (SharedData[7] >> 6)| ((SharedData[6] & 0x0B) >> 6);// bitpos :54 no of bits: 10
	velocityValue = velocityValue - 55;
	auto velocity_kmh = static_cast<float>(velocityValue);
	velocity_kmh = std::min(velocity_kmh, velocity_max_kmh); // Ensure it's within maximum velocity
	const auto use_kmh = (_unit_velocity == Units::UnitVelocity::KilometersPerHour);
	const auto velocity_normalized = use_kmh ? (velocity_kmh / velocity_max_kmh) : (Units::kmhToMph(velocity_kmh) / velocity_max_mph);
	const auto needle_angle = (velocity_normalized - 0.5f) * PI;

	// map speed from 0..60 km/h or 0..40 mph
	if (_needle_update_required || fabs(_needle_angle - needle_angle) > 0.003f)
	{
		_needle_angle = needle_angle;
		needle.invalidateContent(); // invalidate the old needle range
		needle.setZAngle(_needle_angle);
		needle.invalidateContent(); // invalidate the new needle range
		_current_highlight->updateArc(-90.0f, _needle_angle * RADTODEG);
		_needle_update_required = false;
	}

	// update displayed velocity if needed
	const auto displayed_velocity = static_cast<int32_t>(velocity_kmh);
	if (displayed_velocity != _displayed_velocity)
	{
		_displayed_velocity = displayed_velocity;
		Unicode::snprintf(currentVelocityBuffer, 6, "%d", _displayed_velocity);
		currentVelocity.invalidate();
	}


	bool high_beam_var   =     (((int)frame_102h[0]) & (1<<2));//bitpos 2 0x20 //done
	bool side_stand_var      = (((int)frame_102h[0]) & (1<<4));//bitpos 4 0x08 //done
	bool left_indiciator_var  = (((int)frame_102h[2]) & (1<<1)); //bitpos 17 0x40 //done
	bool right_indicator_var  = (((int)frame_102h[2]) & (1<<2)); //bitpos 18 0x20 //done
	bool aux_discg_var       = (((int)frame_102h[0]) & (1<<6)); //bitpos 6 0x04//done //low battery
	bool hazard_var          =  (((int)frame_102h[7]) & (1<<5));//bitpos 61 0x04 //done

	if(left_indiciator_var == true)
	{
		indi_left.setVisible(true);
		indi_left.invalidate();
	}
	else
	{
		indi_left.setVisible(false);
		indi_left.invalidate();
	}
	if(right_indicator_var == true)
	{
		indi_right.setVisible(true);
		indi_right.invalidate();

	}
	else
	{
		indi_right.setVisible(false);
		indi_right.invalidate();
	}
	if(side_stand_var == true)
	{
		side_stand.setVisible(true);
		side_stand.invalidate();
	}
	else
	{
		side_stand.setVisible(false);
		side_stand.invalidate();

	}
	if(aux_discg_var == true)
	{
		aux_L.setVisible(true);
		aux_L.invalidate();
	}
	else
	{
		aux_L.setVisible(false);
		aux_L.invalidate();
	}
	if(high_beam_var == true)
	{
		high_beam.setVisible(true);
		high_beam.invalidate();
	}
	else
	{
		high_beam.setVisible(false);
		high_beam.invalidate();

	}

	if(hazard_var == true)
	{
		fault.setVisible(true);
		fault.invalidate();
	}
	else
	{
		fault.setVisible(false);
		fault.invalidate();
	}

	char k = 'K';
	char m = 'm';

	// update displayed total distance if needed
	uint32_t displayed_total_distance = 0;
	displayed_total_distance = (int)SharedData[2];//use_kmh ? _speedometer._distance_total_km : Units::kmhToMph(_speedometer._distance_total_km);
	Unicode::snprintf(totalDistanceBuffer, 6, "%d%c%c", displayed_total_distance,k,m);
	totalDistance.invalidate();


	uint32_t data_frame_100 = data_frame_100 = ((frame_100h[7] & 0x0F) << 16) | (frame_100h[6] << 8) | frame_100h[5];   //odo, bitpos: 40, noofbits: 20
	Unicode::snprintf(totalDistance_1Buffer, 10, "%d%c%c", data_frame_100,k,m);
	totalDistance_1.invalidate();


	if(/*driveMode >= 0 && driveMode <= ECOPlus*/driveMode == 0)//off
	{
		modeOff.setSelected(true);
		modeStandard.setSelected(false);
		modeSport.setSelected(false);
		modeMax.setSelected(false);
		modeOff.invalidate();
		modeStandard.invalidate();
		modeMax.invalidate();
		modeSport.invalidate();
	}
	else if(driveMode == 1) //standard
	{
		modeOff.setSelected(false);
		modeStandard.setSelected(true);
		modeSport.setSelected(false);
		modeMax.setSelected(false);
		modeOff.invalidate();
		modeStandard.invalidate();
		modeMax.invalidate();
		modeSport.invalidate();
	}
	else if(/*driveMode > ECO && driveMode <= CITY*/driveMode == 2)//sport
	{
		modeOff.setSelected(false);
		modeStandard.setSelected(false);
		modeSport.setSelected(true);
		modeMax.setSelected(false);
		modeOff.invalidate();
		modeStandard.invalidate();
		modeMax.invalidate();
		modeSport.invalidate();
	}
	else if(/*driveMode > CITY && driveMode <= SPORT*/driveMode == 3) //max
	{
		modeOff.setSelected(false);
		modeStandard.setSelected(false);
		modeSport.setSelected(false);
		modeMax.setSelected(true);
		modeOff.invalidate();
		modeStandard.invalidate();
		modeMax.invalidate();
		modeSport.invalidate();
	}
	else
	{

	}

}

void DashboardView::handleTickEvent()
{
	update();
	_tick_current++;
}


void DashboardView::handleDragEvent(const touchgfx::DragEvent& event)
{
	const auto x1 = static_cast<float>(event.getOldX());
	const auto y1 = static_cast<float>(event.getOldY());

	// disregard drag events not coming from the outer handle
	const auto vx_px = event.getOldX() - screen_center_x;
	const auto vy_px = event.getOldY() - screen_center_y;
	const auto v_length_squared = vx_px * vx_px + vy_px * vy_px;
	if (v_length_squared < outer_handle_distance_squared || vy_px > 0)
	{
		return;
	}

	const auto x2 = static_cast<float>(event.getNewX());
	const auto y2 = static_cast<float>(event.getNewY());

	const auto dx1 = x1 - speedometer_center_x;
	const auto dy1 = y1 - speedometer_center_y;
	const auto dx2 = x2 - speedometer_center_x;
	const auto dy2 = y2 - speedometer_center_y;

	const auto angle_1 = atan2(dy1, dx1);
	const auto angle_2 = atan2(dy2, dx2);
	const auto delta_angle = static_cast<float>(angle_2 - angle_1);

	// disregard jumps when user spins the handle too far
	if (static_cast<float>(fabs(delta_angle)) > PI_2)
	{
		return;
	}

	// user wants to set the speed by controlling the speedometer needle. from this point on,
	// the speed simulation is disabled and the user keeps controlling the needle until enough
	// ticks without any user-driven event have passed.
	_needle_angle += delta_angle;
	clamp(_needle_angle, PI_2, -PI_2);
	_tick_user_input = _tick_current;
	_tick_user_input_has_value = true;
	_needle_update_required = true;
}


void DashboardView::selectKmh()
{
	_unit_velocity = Units::UnitVelocity::KilometersPerHour;
	_unit_length = Units::UnitLength::Meters;
	_current_highlight = &highlightKmh;
	_needle_update_required = true;

	// gotta update the speedometer values before showing the circles
	// otherwise there'd be a frame where the velocity is inconsistent with the ui
	updateSpeedometer(1.0f);
}


void DashboardView::selectMiles()
{
	_unit_velocity = Units::UnitVelocity::MilesPerHour;
	_unit_length = Units::UnitLength::Feet;
	_current_highlight = &highlightMph;
	_needle_update_required = true;

	updateSpeedometer(1.0f);
}


bool Battery::update(float dt)
{
	auto changed = false;
	_elapsed_time_ticks += dt;

	if ((static_cast<uint32_t>(_elapsed_time_ticks) % 30) == 0)
	{
		_remaining_s--;

		if (_remaining_s == 0)
		{
			_remaining_s = battery_duration_s;
		}

		changed = true;
	}

	_battery_state = static_cast<float>(_remaining_s) / static_cast<float>(battery_duration_s);

	// battery step should range from 0..5
	// it's rather a UI-related thing but computing it here helps avoiding to update the UI too often
	const auto battery_state_step_tmp = std::min<int32_t>(5, static_cast<int32_t>(_battery_state * 6.0f));
	if (battery_state_step_tmp != _battery_state_step)
	{
		_battery_state_step = battery_state_step_tmp;
		changed = true;
	}

	return changed;

	///user added
	//user added end
}

float Speedometer::computeVelocity(float time) const

{
	return 30.0f + static_cast<float>(std::sin(0.01f * time)) * 20.0f;;
}


bool Speedometer::update(float dt)
{
	_elapsed_time_ticks += dt;

	// todo, incorporate altitude
	// speed just depends on altitude
	_altitude_m = 0.0f;
	_velocity_kmh = computeVelocity(_elapsed_time_ticks);
	_distance_total_km += _velocity_kmh * 0.00001f;

	const auto changed = (fabs(_velocity_kmh - _velocity_prev_kmh) > 0.05f);

	return changed;
}


float Units::metersToFeet(float m)
{
	return 3.28084f * m;
}


float Units::kmhToMph(float kmh)
{
	return 0.621371f * kmh;
}



bool ElevationSimulation::update(float dt)
{
	bool elevationUpdated = false;
	static uint64_t count = 0;
	time += dt;

	if (count % 2 == 0)
	{
		_elevation_m = frame_105h[4];//+ 60 * sin(time * 0.014f) + 30 * sin(time * 0.035f) + 30 * sin(time * 0.060f);;//127.0f + (60 * sin(count * 0.014f) + 30 * sin(count * 0.035f) + 30 * sin(count * 0.060f));
		elevationUpdated = true; //true in default
	}
	count++;

	return elevationUpdated;
}

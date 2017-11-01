#include <acknex.h>
#include <default.c>
#include <ackphysx.h>

ENTITY* playermodel; //need to declare entities here
ENTITY* SoccerBall;
ENTITY* playertwomodel;
ENTITY* myStaticModel;
ENTITY* AIOne;
ENTITY* AI2;
ENTITY* AI3;
ENTITY* AI4;
ENTITY* goal_LEFT;
ENTITY* goal_RIGHT;
ENTITY* goal_TOP;
ENTITY* goal_two_LEFT;
ENTITY* goal_two_RIGHT;
ENTITY* goal_two_TOP;
SOUND* footstep = "footstepSound.wav";
SOUND* kick = "Kick.wav";

var playeronescore = 0, playertwoscore = 0, playerhit = 0;
STRING* PLAYERSCOREONE = "0";
STRING* PLAYERSCORETWO = "0";

var snd_handle1, snd_handle2, snd_handle3, snd_handle4; // these are the variabes that will handle the sound action
random_seed(0);

var tempO[3]; //temp for orbit

		var 	cam_dist=65;
		var 	rotspd=1;
		ANGLE cam_ang;
		var 	minang= 15;
		var 	maxang=70;
		var 	mindist=10;
		var 	maxdist=2000;



VECTOR vSpeed, vAngularSpeed, vForce, vMove;

TEXT* Score = { 
   pos_x = 10; pos_y = 10;
   font = "Arial#18bi";
   flags = SHADOW;
   string("SCORES:",
          "Player 1: ", PLAYERSCOREONE, 
          "Player 2: ", PLAYERSCORETWO); 
}
	
function round(var x)
{
	return floor(x+0.5);
}	


// simple function for walking over ground
// control the player with the WASD keys
// player origin must be at the model center
// bounding box must be smaller than the player!
action player_walk()
{ 
set(my,NARROW); 
set(my,FAT);
wait(1);
c_setminmax(my);
vec_set(my.min_x,vector(-1.7,-1.7,0));
vec_set(my.max_x,vector(1.7,1.7,9.5));

 

// if necessary, adjust the bounding box to give the entity 'floor room' (see remarks) 
   //my.min_z *= 0.5;

   var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   VECTOR vFeet;
   vec_for_min(vFeet,me); // vFeet.z = distance from player origin to lowest vertex
   //my.NARROW = ON;   

   while (1)
   {
// rotate the player using the [A] and [D] keys      
      my.pan += 15*(key_a-key_d)*time_step;   
         

// move the player using the [W] and [S] keys      
      var dist_ahead = 1*(key_w-key_s)*time_step;
      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.05);
      /*float value at end of dist_ahead adjusts how fast the player moves
      need to adjust this value in tandem with anim_percent below
      to correct synchronise and animation functions */
      
      c_move(me,vector(0,-dist_ahead,0),vector(0,0,-5*time_step),IGNORE_PASSABLE | GLIDE); // move the player

// animate the player according to its moved distance
      if (dist_ahead != 0) // player is moving ahead
      {
         anim_percent += 1*dist_ahead; // 1 = walk cycle percentage per quant, adjust for animation speed
         ent_animate(me,"walk",anim_percent,ANM_CYCLE); // play the "walk" animation

// add some footstep sounds here synchronised with individual frames of the animation
			//play left footstep sounds
         if(((my.frame >= 5 && my.frame <= 6)||(my.frame >= 21 && my.frame <= 22)||(my.frame >= 41 && my.frame <= 42))
         	 && (snd_playing(snd_handle1) == 0)) {
         	snd_handle1 = snd_play(footstep,100,0);
         }
         
         //play right footstep sounds
         if(((my.frame >= 13 && my.frame <= 14)||(my.frame >= 33 && my.frame <= 34)||(my.frame >= 50 && my.frame <= 51))
         	 && (snd_playing(snd_handle2) == 0)) {
         	snd_handle2 = snd_play(footstep,100,0);
         }
      }
      else // player stands still
      { 
         anim_percent += 5*time_step; 
         ent_animate(me,"stand",anim_percent,ANM_CYCLE); // play the "stand" animation
      }
      wait(1);
      
   }
}

action playerTwoWalk()
{ 
set(my,NARROW); 
set(my,FAT);
wait(1);
c_setminmax(my);
vec_set(my.min_x,vector(-1.7,-1.7,0));
vec_set(my.max_x,vector(1.7,1.7,9.5));

 

// if necessary, adjust the bounding box to give the entity 'floor room' (see remarks) 
   //my.min_z *= 0.5;

   var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   VECTOR vFeet;
   vec_for_min(vFeet,me); // vFeet.z = distance from player origin to lowest vertex
   //my.NARROW = ON;   

   while (1)
   {
// rotate the player using the [A] and [D] keys      
      my.pan += 15*(key_cul-key_cur)*time_step;   
         

// move the player using the [W] and [S] keys      
      var dist_ahead = 1*(key_cuu-key_cud)*time_step;
      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.05);
      /*float value at end of dist_ahead adjusts how fast the player moves
      need to adjust this value in tandem with anim_percent below
      to correct synchronise and animation functions */
      
      c_move(me,vector(0,-dist_ahead,0),vector(0,0,-5*time_step),IGNORE_PASSABLE | GLIDE); // move the player

// animate the player according to its moved distance
      if (dist_ahead != 0) // player is moving ahead
      {
         anim_percent += 1*dist_ahead; // 1 = walk cycle percentage per quant, adjust for animation speed
         ent_animate(me,"walk",anim_percent,ANM_CYCLE); // play the "walk" animation

// add some footstep sounds here synchronised with individual frames of the animation
			//play left footstep sounds
         if(((my.frame >= 5 && my.frame <= 6)||(my.frame >= 21 && my.frame <= 22)||(my.frame >= 41 && my.frame <= 42))
         	 && (snd_playing(snd_handle1) == 0)) {
         	snd_handle1 = snd_play(footstep,100,0);
         }
         
         //play right footstep sounds
         if(((my.frame >= 13 && my.frame <= 14)||(my.frame >= 33 && my.frame <= 34)||(my.frame >= 50 && my.frame <= 51))
         	 && (snd_playing(snd_handle2) == 0)) {
         	snd_handle2 = snd_play(footstep,100,0);
         }
      }
      else // player stands still
      { 
         anim_percent += 5*time_step; 
         ent_animate(me,"stand",anim_percent,ANM_CYCLE); // play the "stand" animation
      }
      wait(1);
      
   }
}

action artificial_movement()
{
	set(my,NARROW); 
	set(my,FAT);
	wait(1);
	c_setminmax(my);
	vec_set(my.min_x,vector(-1.7,-1.7,0));
	vec_set(my.max_x,vector(1.7,1.7,9.5));
	
	var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   VECTOR vFeet;
   vec_for_min(vFeet,me);
   
   var y = random(100);
   
   while(1)
   {
   	if (y<0)
   	{
   		var x = random(180) - 90;
   		my.pan += 15 * x * time_step;
   		y = random(100);
   	}
   		y = y-1;
   		var dist_ahead = 20*time_step;
      	dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.05);
      	c_move(me,vector(0,-dist_ahead,0),vector(0,0,-5*time_step),IGNORE_PASSABLE | GLIDE);
      
      
      	if (dist_ahead != 0) // player is moving ahead
      	{
         	anim_percent += 1*dist_ahead; // 1 = walk cycle percentage per quant, adjust for animation speed
         	ent_animate(me,"walk",anim_percent,ANM_CYCLE); // play the "walk" animation

			// add some footstep sounds here synchronised with individual frames of the animation
				//play left footstep sounds
      	   if(((my.frame >= 5 && my.frame <= 6)||(my.frame >= 21 && my.frame <= 22)||(my.frame >= 41 && my.frame <= 42))
         		 && (snd_playing(snd_handle1) == 0)) {
         		snd_handle1 = snd_play(footstep,100,0);
         	}
         
         	//play right footstep sounds
         	if(((my.frame >= 13 && my.frame <= 14)||(my.frame >= 33 && my.frame <= 34)||(my.frame >= 50 && my.frame <= 51))
         		 && (snd_playing(snd_handle2) == 0)) {
         		snd_handle2 = snd_play(footstep,100,0);
         	}
      	}
      	else // player stands still
      	{ 
         	anim_percent += 5*time_step; 
         	ent_animate(me,"stand",anim_percent,ANM_CYCLE); // play the "stand" animation
      	}
      	wait(10);
      	
      	
      	if (my.y > 300 || my.y < -340 || my.x < -250 || my.x > 175)
      	{
      		my.pan += 180;	
			}
	}
   	
}



function main()
{
	physX_open();
   video_mode = 7;
   //video_screen = 1; //full screen
	shadow_stencil = 0;
	mtl_shadow.alpha = 65;
	d3d_antialias = 1;
	sky_color.red = 75;
	sky_color.green = 0;
	sky_color.blue = 75;
	
	set(Score, VISIBLE);

	wait(3);

	level_load("terrainMap.hmp"); //terrain
	
	playermodel = ent_create("animChr11.mdl",vector(-32.5,-75,0),player_walk); //character
	playermodel.scale_x = 4.0;
	playermodel.scale_y = 4.0;
	playermodel.scale_z = 4.0;
	
	playertwomodel = ent_create("animChr11.mdl", vector(-32.5,30, 0), playerTwoWalk);
	playertwomodel.scale_x = 4.0;
	playertwomodel.scale_y = 4.0;
	playertwomodel.scale_z = 4.0;
	
	AIOne = ent_create("animChr11.mdl", vector(0, 50, 0), artificial_movement);
	AIOne.scale_x = 4.0;
	AIOne.scale_y = 4.0;
	AIOne.scale_z = 4.0;
	
	AI2 = ent_create ("animChr11.mdl", vector(50, 0, 0), artificial_movement);
	AI2.scale_x = 4.0;
	AI2.scale_y = 4.0;
	AI2.scale_z = 4.0;
	
	AI3 = ent_create ("animChr11.mdl", vector(0, -50, 0), artificial_movement);
	AI3.scale_x = 4.0;
	AI3.scale_y = 4.0;
	AI3.scale_z = 4.0;
	
	AI4 = ent_create ("animChr11.mdl", vector(-50, 0, 0), artificial_movement);
	AI4.scale_x = 4.0;
	AI4.scale_y = 4.0;
	AI4.scale_z = 4.0;
	
	SoccerBall = ent_create("SoccerBall.mdl", vector(-32.5,-20,0), NULL);
	SoccerBall.scale_x = 3.0;
	SoccerBall.scale_y = 3.0;
	SoccerBall.scale_z = 3.0;
	set(SoccerBall, SHADOW);
	
	set(playermodel,SHADOW); //casts shadow for player
	set(playermodel,SHADOW);
	
	//myStaticModel = ent_create("my_StaticModel.mdl",vector(-200,-50,30),NULL);
	//myStaticModel.scale_x = 10.0;
	//myStaticModel.scale_y = 10.0;
	//myStaticModel.scale_z = 10.0;
	
	goal_LEFT = ent_create("Goal_Left.mdl", vector(-32.5, 300, 0), NULL);
	goal_LEFT.scale_x = 0.1;
	goal_LEFT.scale_y = 0.1;
	goal_LEFT.scale_z = 0.1;
	
	goal_RIGHT = ent_create("Goal_Right.mdl", vector(-32.5,300, 0), NULL);
	goal_RIGHT.scale_x = 0.1;
	goal_RIGHT.scale_y = 0.1;
	goal_RIGHT.scale_z = 0.1;
	
	goal_TOP = ent_create("Goal_Top.mdl", vector(-32.5,300,0), NULL);
	goal_TOP.scale_x = 0.1;
	goal_TOP.scale_y = 0.1;
	goal_TOP.scale_z = 0.1;
	
	goal_two_LEFT = ent_create("Goal_Left.mdl", vector(-32.5,-340,0), NULL);
	goal_two_LEFT.scale_x = 0.1;
	goal_two_LEFT.scale_y = 0.1;
	goal_two_LEFT.scale_z = 0.1;
	
	goal_two_RIGHT = ent_create("Goal_Right.mdl", vector(-32.5,-340,0), NULL);
	goal_two_RIGHT.scale_x = 0.1;
	goal_two_RIGHT.scale_y = 0.1;
	goal_two_RIGHT.scale_z = 0.1;
	
	goal_two_TOP = ent_create("Goal_Top.mdl", vector(-32.5,-340,0), NULL);
	goal_two_TOP.scale_x = 0.1;
	goal_two_TOP.scale_y = 0.1;
	goal_two_TOP.scale_z = 0.1;
	
	
	
	//set(myStaticModel,SHADOW); //casts shadow for Liberty statue
	//set(myStaticModel,POLYGON); //bounding box shap of object
	
	pXent_settype(SoccerBall,PH_RIGID,PH_SPHERE);
	pXent_setelasticity(SoccerBall,80);
	pXent_setdamping(SoccerBall,50,50);
	pXent_setmass(SoccerBall,0.01);//mass of ball
	pX_setgravity(vector(0,0,-1));//gravity
	


	while(1)
	{
		mouse_pos.x = mouse_cursor.x; // allow the mouse pointer to move
		mouse_pos.y = mouse_cursor.y; // on the x and y axis

	int kickStrength = 10;
	if(vec_dist(playermodel.x, SoccerBall.x)<5) {
		if(snd_playing(snd_handle3) == 0)
		{
			snd_handle3 = snd_play(kick, 50, 0);
		}
		VECTOR kick;
		vec_set(kick,SoccerBall.x);
		vec_sub(kick,playermodel.x);
		vec_normalize(kick,kickStrength);
		pXent_addvelcentral(SoccerBall,kick);
		playerhit = 1;
		
	}
	if(vec_dist(playertwomodel.x, SoccerBall.x)<5) {
		if(snd_playing(snd_handle4) == 0)
		{
			snd_handle4 = snd_play(kick, 50, 0);
		}
		VECTOR kick;
		vec_set(kick,SoccerBall.x);
		vec_sub(kick,playertwomodel.x);
		vec_normalize(kick,kickStrength);
		pXent_addvelcentral(SoccerBall,kick);
		playerhit = 2;
	}
	int kickStrength = 10;
	if(vec_dist(AIOne.x, SoccerBall.x)<5) {
		if(snd_playing(snd_handle3) == 0)
		{
			snd_handle3 = snd_play(kick, 50, 0);
		}
		VECTOR kick;
		vec_set(kick,SoccerBall.x);
		vec_sub(kick,AIOne.x);
		vec_normalize(kick,kickStrength);
		pXent_addvelcentral(SoccerBall,kick);
		playerhit = 1;
		
	}
	if(vec_dist(AI2.x, SoccerBall.x)<5) {
		if(snd_playing(snd_handle3) == 0)
		{
			snd_handle3 = snd_play(kick, 50, 0);
		}
		VECTOR kick;
		vec_set(kick,SoccerBall.x);
		vec_sub(kick,AI2.x);
		vec_normalize(kick,kickStrength);
		pXent_addvelcentral(SoccerBall,kick);
		playerhit = 1;
		
	}
	
	if(vec_dist(AI3.x, SoccerBall.x)<5) {
		if(snd_playing(snd_handle3) == 0)
		{
			snd_handle3 = snd_play(kick, 50, 0);
		}
		VECTOR kick;
		vec_set(kick,SoccerBall.x);
		vec_sub(kick,AI3.x);
		vec_normalize(kick,kickStrength);
		pXent_addvelcentral(SoccerBall,kick);
		playerhit = 1;
		
	}
	
	if(vec_dist(AI4.x, SoccerBall.x)<5) {
		if(snd_playing(snd_handle3) == 0)
		{
			snd_handle3 = snd_play(kick, 50, 0);
		}
		VECTOR kick;
		vec_set(kick,SoccerBall.x);
		vec_sub(kick,AI4.x);
		vec_normalize(kick,kickStrength);
		pXent_addvelcentral(SoccerBall,kick);
		playerhit = 1;
		
	}
	
	
	if((SoccerBall.y > 300 | SoccerBall.y < -340) & SoccerBall.x < -17.5 & SoccerBall.x > -47.5)
	{
		ent_remove(SoccerBall);
		SoccerBall = ent_create("SoccerBall.mdl", vector(-33.5,-20,10), NULL);
		SoccerBall.scale_x = 3.0;
		SoccerBall.scale_y = 3.0;
		SoccerBall.scale_z = 3.0;
		set(SoccerBall, SHADOW);
		pXent_settype(SoccerBall,PH_RIGID,PH_SPHERE);
		pXent_setelasticity(SoccerBall,80);
		pXent_setdamping(SoccerBall,50,50);
		pXent_setmass(SoccerBall,0.01);//mass of ball
		pX_setgravity(vector(0,0,-1));//gravity
		
		if (playerhit == 1)
		{
			playeronescore++;
			str_for_num(PLAYERSCOREONE, playeronescore);
		} else if (playerhit == 2)
		{
			playertwoscore++;
			str_for_num(PLAYERSCORETWO, playertwoscore);
		}
		
	}
	
	wait(1);
	
		//camera move
		if(mouse_right)
		{
			
			cam_ang.pan+= (-rotspd*mouse_force.x)*1;
			cam_ang.tilt+= (-rotspd*mouse_force.y)*1;
			cam_ang.tilt=clamp(cam_ang.tilt,minang,maxang);
			
		}

			// zoom with mousewheel
			cam_dist-=integer(mickey.z)*0.1;
			cam_dist=clamp(cam_dist,mindist,maxdist);
			
			// do some trig to find camera location and then aim it at pFocus
			camera.x=playermodel.x+cos(cam_ang.pan)*(cam_dist*cos(cam_ang.tilt));
			camera.y=playermodel.y+sin(cam_ang.pan)*(cam_dist*cos(cam_ang.tilt));
			camera.z=playermodel.z+sin(cam_ang.tilt)*cam_dist;
			vec_set(tempO,playermodel.x);
			vec_sub(tempO,camera.x);
			vec_to_angle(camera.pan,tempO);
			
		
		//vForce.x = 3 * (key_cuu - key_cud);		// forward
		//vForce.y = 3 * (key_cul - key_cur);		// sideward
		vForce.z = 3 * (key_pgup - key_pgdn);	// up/down
		vec_accelerate(vMove,vSpeed,vForce,0.5);
		vec_rotate(vMove,camera.pan);
		vec_add(camera.x,vMove);//moves camera with arrow keys
		vec_add(playermodel.x,vMove);//moves pFocus with camera/arrow keys
				
				//stops player from falling through groundplane
				//if (playertwomodel.z < 1)
				//{playertwomodel.z = 1;}
				//stop player from falling off edge of terrain (set to actual terrain dimensions)
			/*	if (playermodel.x > 600)
				{playermodel.x = 600;}
				if (playermodel.x < -600)
				{playermodel.x = -600;}
				if (playermodel.y > 600)
				{playermodel.y = 600;}
				if (playermodel.y < -600)
				{playermodel.y = -600;}*/
				
		wait(1);
	}	


}

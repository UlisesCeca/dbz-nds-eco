bool _SpriteTouched(u8 n){
	touchPosition sprTouch;
	touchRead(&sprTouch);
	if((sprTouch.px>=NF_SPRITEOAM[1][n].x) && (sprTouch.py>=NF_SPRITEOAM[1][n].y) && (sprTouch.px<=NF_SPRITEOAM[1][n].x+NF_SPR256VRAM[1][n].width) && (sprTouch.py<=NF_SPRITEOAM[1][n].y+NF_SPR256VRAM[1][n].height)){
		return 1;
	}else{
		return 0;
	}
}

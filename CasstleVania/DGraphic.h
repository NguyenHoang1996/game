#ifndef _DXGRAPHICS_H
#define _DXGRAPHICS_H

/*Function prototypes*/
int Init_Direct3D(HWND, int, int);
LPDIRECT3DSURFACE9 LoadSurface(char *, D3DCOLOR);
LPDIRECT3DTEXTURE9 LoadTexture(LPWSTR , D3DCOLOR);
#endif
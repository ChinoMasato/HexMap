
# include <Siv3D.hpp> // Siv3D v0.6.12
const int MapHeight = 12;
const int MapWidth = 20;
ColorF mapcolor[MapHeight][MapWidth];
double tilesize = 500 / MapWidth;
bool setData(int i, int j, ColorF& mapdata)
{
	if (i < 0 || i >= MapHeight || j < 0 || j >= MapWidth) return false;

	mapcolor[i][j] = mapdata;
	return true;
}
void war(int i, int j)
{
	int r = Random(5);
	if (r == 0)
	{
		if (j % 2 == 1) {
			//左上に攻め込む
			setData(i,j - 1,mapcolor[i][j]);
		}
		else {
			setData(i-1,j - 1,mapcolor[i][j]);
		}
	}
	if (r == 1)
	{
		//上に攻め込む
		setData(i - 1,j,mapcolor[i][j]);

	}

	if (r == 2 )
	{
		if (j % 2 == 1) {
			//右上に攻め込む
			setData(i,j + 1,mapcolor[i][j]);
		}
		else {
			//右上に攻め込む
			setData(i-1,j + 1,mapcolor[i][j]);
		}
	}
	if (r == 3 )
	{
		if (j % 2 == 1) {
			//左下に攻め込む
			setData(i + 1,j - 1,mapcolor[i][j]);
		}
		else {
			setData(i, j - 1, mapcolor[i][j]);
		}
	}
	if (r == 4)
	{
		//下に攻め込む
		setData(i + 1,j,mapcolor[i][j]);
	}
	if (r == 5)
	{
		if (j % 2 == 1) {
			//右下に攻め込む
			setData(i + 1,j+1,mapcolor[i][j]);
		}
		else {
			setData(i, j + 1, mapcolor[i][j]);
		}
	}
}
void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// マルチサンプル・レンダーテクスチャ
	const MSRenderTexture msRenderTexture{ 800, 600, Palette::White };
	//初期化
	for (int i = 0; i < MapHeight; ++i)
	{
		for (int j = 0; j < MapWidth; ++j)
		{
			mapcolor[i][j] = ColorF{ Random(1.0),Random(1.0),Random(1.0),1.0 };
		}
	}
	while (System::Update())
	{

		//行動
		for (int i = 0; i < MapHeight* MapWidth/10; ++i) {
			war(Random(MapHeight - 1), Random(MapWidth - 1));
		}
		//描画
		for (int i = 0; i < MapHeight; ++i)
		{
			for (int j = 0; j < MapWidth; ++j)
			{
				int shift = 0;
				if(j%2==1){
					shift = tilesize *0.5 * sqrt(3);
				}
				const ScopedRenderTarget2D target{ msRenderTexture.clear(Palette::Black) };
				Shape2D::Hexagon(tilesize, { j * tilesize *1.5+ tilesize,i * tilesize *sqrt(3) + shift+ tilesize },  30_deg).draw(mapcolor[i][j]);
				ColorF bordercolor = mapcolor[i][j];
				bordercolor.a = 0.5;
				Shape2D::Hexagon(tilesize, { j * tilesize * 1.5 + tilesize,i * tilesize * sqrt(3) + shift + tilesize }, 30_deg).drawFrame(tilesize / 20, Palette::White);
				//Shape2D::Hexagon(tilesize, { j * tilesize * 1.5+ tilesize,i * tilesize * sqrt(3) + shift + tilesize }, 30_deg).drawFrame(tilesize/10, bordercolor);
			}
		}
		// 2D 描画をフラッシュ
		Graphics2D::Flush();

		// マルチサンプル・テクスチャをリゾルブ
		msRenderTexture.resolve();
		msRenderTexture.draw(0, 0);
	}
}



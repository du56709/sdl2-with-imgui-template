// Using nlohmann json

std::ifstream infile(argv[1]);
json jin = json::parse(infile);

std::vector<Triangle3D> level_geometry;

for(unsigned i = 0; i < jin.size(); i++)
{
	//std::cout << jin[i].dump(4) << std::endl;
	// Process json input
	//std::cout << jin[i].at("material") << std::endl;
	//std::cout << jin[i].at("poly") << std::endl;
	
	Triangle3D t;
	
	if(jin[i].at("poly").size() == 3)
	{
		auto p1 = jin[i].at("poly")[0];
		auto p2 = jin[i].at("poly")[1];
		auto p3 = jin[i].at("poly")[2];
		
		t.p[0] = {(float(p1[0])), (float(p1[1])), (float(p1[2]))};
		t.p[1] = {(float(p2[0])), (float(p2[1])), (float(p2[2]))};
		t.p[2] = {(float(p3[0])), (float(p3[1])), (float(p3[2]))};
		
		level_geometry.push_back(t);
	}
}

#include "actions_newtorus.h"
#include "potential_factory.h"
#include "orbit.h"
#include <variant>
#include <vector>
#include <iostream>
#include <format> 
#include <fstream>
#include <stdio.h>

int main(){
    potential::PtrPotential pot=potential::createPotential(utils::KeyValueMap("type=spheroid,alpha=1,gamma=1,beta=3, outerCutoffRadius=10,q=0.8"));
    actions::Actions J(.2,.3,3);
	actions::TorusGenerator TG(*pot);
	actions::Torus T(TG.fitTorus(J));
	actions::Angles ttr(0.5,0.3,0.2);
	coord::PosVelCyl xv0=coord::toPosVelCyl(T.from_true(ttr));
	std::vector<std::pair<coord::PosVelCyl,double>> traj=orbit::integrateTraj(xv0,400,1,*pot);
	std::vector<std::pair<coord::PosVelCyl,double>> traj2=T.orbit(ttr,1,400);
	int N=traj.size();
	if(traj2.size()<N)N=traj2.size();
	std::ofstream file("Rzvals.txt");
	for(int i=0;i<N;i++){
		file<<traj[i].second<<" "<<traj[i].first.R<<" "<<traj[i].first.z<<" "
		<<traj2[i].second<<" "<<traj2[i].first.R<<" "<<traj2[i].first.z<<"\n";
	}
	file.close();
    return 0;
}
# Fisica_Experimental_Particulas_2021_2
This respository is oriented to resolve the activities related to the course

## TT-Bar Semi-leptonic Selection
### Cutflow
> <img src="tt-bar/HGraphs/cutflow.png" width="380"> <img src="tt-bar/HGraphsMC/cutflow.png" width="380">
### Leptons
> <img src="tt-bar/HGraphs/hist_lept_pt.png" width="380"> <img src="tt-bar/HGraphsMC/hist_lept_pt.png" width="380">
> <img src="tt-bar/HGraphs/hist_lept_pt_cone30.png" width="380"> <img src="tt-bar/HGraphsMC/hist_lept_pt_cone30.png" width="380">
> <img src="tt-bar/HGraphs/hist_lept_et_cone20.png" width="380"> <img src="tt-bar/HGraphsMC/hist_lept_et_cone20.png" width="380">
> <img src="tt-bar/HGraphs/hist_lept_eta.png" width="380"> <img src="tt-bar/HGraphsMC/hist_lept_eta.png" width="380">
### Jets
> <img src="tt-bar/HGraphs/hist_njets.png" width="380"> <img src="tt-bar/HGraphsMC/hist_njets.png" width="380">
> <img src="tt-bar/HGraphs/hist_jets_pt.png" width="380"> <img src="tt-bar/HGraphsMC/hist_jets_pt.png" width="380">
> <img src="tt-bar/HGraphs/hist_jets_eta.png" width="380"> <img src="tt-bar/HGraphsMC/hist_jets_eta.png" width="380">
> <img src="tt-bar/HGraphs/hist_jets_JVF.png" width="380"> <img src="tt-bar/HGraphsMC/hist_jets_JVF.png" width="380">
> <img src="tt-bar/HGraphs/hist_jets_MV1.png" width="380"> <img src="tt-bar/HGraphsMC/hist_jets_MV1.png" width="380">
### b-Jets
> <img src="tt-bar/HGraphs/hist_nbjets.png" width="380"> <img src="tt-bar/HGraphsMC/hist_nbjets.png" width="380">
### MET
<img src="tt-bar/HGraphs/hist_MET.png" width="380"> <img src="tt-bar/HGraphsMC/hist_MET.png" width="380">
### mTW
<img src="tt-bar/HGraphs/hist_mTW.png" width="380"> <img src="tt-bar/HGraphsMC/hist_mTW.png" width="380">

## Tracks and Clusters
### Exercise 1 & 2 
> We make three histograms through the **'TC_Ex1_2_macro.cpp'** file, so these graphs are as following:
> <img src="Tracks_Clusters/mu_mean.png" width="500"> <img src="Tracks_Clusters/npv.png" width="500"> <img src="Tracks_Clusters/npv_mu.png" width="500">
>
>These 3 histogram are about 1. Number of average interaction per bunch-crossing (Events vs mu_average) 2. Number of primary vertices per event (Events vs NPV) and 3. A 2D histogram to analyze the number of primary vertices per number of average interaction (NPV vs mu_average)
### Exercise 3
> Because tracks and clusters information is not such an event variable, but objects with some kinematical information, we make a 2D histogram to view how is the behavior related to the previous variable and the number of tranks and clusters per event, this is made in **'TC_Ex3_macro.cpp'** file and it's shown in following images:
> 
> <img src="Tracks_Clusters/npv_Tck.png" width="500"> <img src="Tracks_Clusters/mu_Tck.png" width="500"> <img src="Tracks_Clusters/npv_Clt.png" width="500"> <img src="Tracks_Clusters/mu_Clt.png" width="500">
### Exercise 4, 5 & 6
> Now we print histograms related to the track and cluster variables, this information is associeted when particles go throughout trackers and calorimeters, moreover it's compared to particle variables that correspond to simulations of experimental results. So this was made through **'TC_Ex4_5_6_macro.cpp'** file.
> * **Track Variables**
> 
> <img src="Tracks_Clusters/Track_pt.png" width="350"> <img src="Tracks_Clusters/Track_eta.png" width="350">
> <img src="Tracks_Clusters/Track_phi.png" width="350"> <img src="Tracks_Clusters/Track_m.png" width="350"> <img src="Tracks_Clusters/Track_vtx.png" width="350">
>
> * **Cluster Variables**
> 
> <img src="Tracks_Clusters/Cluster_pt.png" width="350"> <img src="Tracks_Clusters/Cluster_eta.png" width="350">
> <img src="Tracks_Clusters/Cluster_phi.png" width="350"> <img src="Tracks_Clusters/Cluster_m.png" width="350">
> 
> * **Particle Variables**
> 
> <img src="Tracks_Clusters/Particle_pt.png" width="350"> <img src="Tracks_Clusters/Particle_eta.png" width="350">
> <img src="Tracks_Clusters/Particle_phi.png" width="350"> <img src="Tracks_Clusters/Particle_m.png" width="350">
> <img src="Tracks_Clusters/Particle_pdgID.png" width="350">
> 
> Finally, in both track and cluster variable are found 'pT', 'eta', 'phi' , 'm', and 'vtx' in the case of track, this correspond to certain beam's properties, i.e., **transversal mommentum**, **psedu-rapidity** (??), **azimuthal angle** (??) and **mass** respectively, 'vtx' is the vertex where come particles from. On other hand, in particle variables we found 'pdgID' corresponding to **Particle Data Group ID** which sort each particle.


## Jets
### Exercise 1

> <img src="Jets/Graphs/WleadR_T.png" width="350"> <img src="Jets/Graphs/WR_T.png" width="350"> <img src="Jets/Graphs/leadR_T.png" width="350"> <img src="Jets/Graphs/R_T.png" width="350">

### Exercise 2

> <img src="Jets/Graphs/Reco_npv.png" width="350"> <img src="Jets/Graphs/Reco_npv_prof.png" width="350"> <img src="Jets/Graphs/Truth_npv.png" width="350"> <img src="Jets/Graphs/Truth_npv_prof.png" width="350">
> <img src="Jets/Graphs/Reco_mu.png" width="350"> <img src="Jets/Graphs/Reco_mu_prof.png" width="350"> <img src="Jets/Graphs/Truth_mu.png" width="350"> <img src="Jets/Graphs/Truth_mu_prof.png" width="350">

### Exercise 3

> <img src="Jets/Graphs/leadR_jvf.png" width="350"> <img src="Jets/Graphs/CleadR_jvf.png" width="350"> <img src="Jets/Graphs/lead_RTruth_cut.png" width="350"> <img src="Jets/Graphs/lead_RTrack_cut.png" width="350">

### Exercise 4

> <img src="Jets/Graphs/DR_RT.png" width="350">

### Exercise 5

> <img src="Jets/Graphs/ReTruth_03.png" width="350"> <img src="Jets/Graphs/traTru_03.png" width="350">

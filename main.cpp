#include <bits/stdc++.h>
#include <memory>

int main()
{
	std::shared_ptr<int> sp1 = std::make_shared<int> (10);
	printf("sp1=%d\n", *sp1);
	auto sp2 = sp1;
	printf("sp2.use_count = %d\n", sp2.use_count());
	std::shared_ptr<std::string> sp3 = std::make_shared<std::string> ("hello zhangheng 1314");
	printf("sp3 = %s\n", (*sp3).c_str());
	std::string s = "abcdefg";
	printf("%s\n", s.c_str());
	return 0;
}

	Eigen::Vector3f e,p;
    p.x() = 4.6;
    p.y() = 1.25;
    p.z() = 0;
    e.x() = 41.9 * M_PI / 180;   //yaw
    e.y() = -1 * M_PI / 180;     //pitch
    e.z() = -0.6 * M_PI / 180;   //roll

    Eigen::Matrix3f rot;
    rot = Eigen::AngleAxisf(e(0), Eigen::Vector3d::UnitZ())
        * Eigen::AngleAxisf(e(1), Eigen::Vector3d::UnitY())
        * Eigen::AngleAxisf(e(2), Eigen::Vector3d::UnitX());
    
    Eigen::Matrix4f m;
    m.setIdentity();
    m.block<3, 3>(0, 0) = rot;
    m.block<3, 1>(0, 3) = p;

    Eigen::Affine3f vlp;
    vlp.matrix() = m;



    PointCloud pointcloud;
    pcl::fromROSMsg(*msg, pointcloud);

    PointCloudPtr base(new PointCloud);
    pcl::transformPointCloud(pointcloud, *base, vlp);
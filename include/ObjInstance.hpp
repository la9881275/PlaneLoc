/*
    Copyright (c) 2017 Mobile Robots Laboratory at Poznan University of Technology:
    -Jan Wietrzykowski name.surname [at] put.poznan.pl

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef INCLUDE_OBJINSTANCE_HPP_
#define INCLUDE_OBJINSTANCE_HPP_

#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

#include <Eigen/Eigen>

#include <pcl/segmentation/supervoxel_clustering.h>
#include <pcl/impl/point_types.hpp>
#include <pcl/surface/convex_hull.h>
#include <pcl/visualization/pcl_visualizer.h>

#include "SegInfo.hpp"

// only planes in a current version
class ObjInstance{
public:
	enum class ObjType{
		Plane,
		Unknown
	};

    /**
     *
     * @param iid
     * @param itype
     * @param ipoints
     * @param isvs
     */
	ObjInstance(int iid,
				ObjType itype,
				pcl::PointCloud<pcl::PointXYZRGB>::Ptr ipoints,
				const std::vector<SegInfo>& isvs);

	inline int getId() const {
		return id;
	}

	inline ObjType getType() const {
		return type;
	}

	inline const pcl::PointCloud<pcl::PointXYZRGB>::Ptr getPoints() const {
		return points;
	}

	inline const std::vector<SegInfo>& getSvs() const {
		return svs;
	}

	inline Eigen::Vector4d getParamRep() const {
		return paramRep;
	}

    inline Eigen::Vector4d getNormal() const {
        return normal;
    }

	inline const pcl::PointCloud<pcl::PointXYZRGB>::Ptr getConvexHull() const {
		return convexHull;
	}

	inline const pcl::PointCloud<pcl::PointXYZRGB>::Ptr getConvexHull(pcl::Vertices& polygon) const {
		polygon = convexHullPolygon;
		return convexHull;
	}

	inline double getConvexHullArea(){
		return chullArea;
	}

	inline const pcl::PointCloud<pcl::PointXYZRGB>::Ptr getConvexHull(pcl::Vertices& polygon,
																	double& area) const {
		polygon = convexHullPolygon;
		area = chullArea;
		return convexHull;
	}

    static std::vector<ObjInstance> mergeObjInstances(const std::vector<std::vector<ObjInstance>>& objInstances,
                                                      pcl::visualization::PCLVisualizer::Ptr viewer = nullptr,
                                                      int viewPort1 = -1,
                                                      int viewPort2 = -1);

	static ObjInstance merge(const std::vector<const ObjInstance*>& objInstances,
                             pcl::visualization::PCLVisualizer::Ptr viewer = nullptr,
                             int viewPort1 = -1,
                             int viewPort2 = -1);

private:
	int id;

	ObjType type;

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr points;

	std::vector<SegInfo> svs;

	Eigen::Vector4d paramRep;

    /**
     * Normal oriented towards observable side.
     */
	Eigen::Vector4d normal;

	float curv;

	double chullArea;

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr convexHull;

	pcl::Vertices convexHullPolygon;
};



#endif /* INCLUDE_OBJINSTANCE_HPP_ */

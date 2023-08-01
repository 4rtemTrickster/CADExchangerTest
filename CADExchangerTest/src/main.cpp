#include <chrono>
#include <corecrt_math_defines.h>
#include <random>
#include <iostream>

#include <CurvesLib.h>
#include <future>


void CreateRandomCurvesCollection(std::vector<std::shared_ptr<ICurve>>& curves_vector);
void GetCirclesFromContainer(const std::vector<std::shared_ptr<ICurve>>& curves_vector,
                             std::vector<std::shared_ptr<Circle>>& circles_vector);

int main()
{
    // Populate a container (e.g. vector or list) of objects of these types created in random manner with random parameters
    std::vector<std::shared_ptr<ICurve>> curves;
    CreateRandomCurvesCollection(curves);


    // Print coordinates of points and derivatives of all curves in the container at t=PI/4.
    std::cout << std::fixed << std::setprecision(2);
    for (auto& curve : curves)
        std::cout << typeid(curve).name() << ": C(t) = " << curve->GetPoint(M_PI_4) <<
            " dC(t)/dt = " << curve->GetFirstDerivative(M_PI_4) << " , where t = PI / 4\n";


    // Populate a second container that would contain only circles from the first container
    std::vector<std::shared_ptr<Circle>> circles;
    GetCirclesFromContainer(curves, circles);
    if (circles.empty()) throw std::runtime_error("The original container does not contain circles");


    
    // Sort the second container in the ascending order of circles’ radii
    std::sort(circles.begin(), circles.end(), [](std::shared_ptr<Circle>& lhs, std::shared_ptr<Circle>& rhs)
    {
        return lhs->GetRadius1() < rhs->GetRadius1();
    });
    // That is, the first element has the smallest radius, the last - the greatest.
    std::cout << "First: " << circles.front()->GetRadius1() << ", last: " << circles.back()->GetRadius1() << "\n";


    
    // any point on helix satisfies the condition C(t + 2*PI) = C(t) + {0, 0, step}.
    Helix h1(
        1, 2, 3, // x, y, z
        5, 5, // a, b
        2,          // step
        M_PI / 3    // angle_start
    );
    
    vec3 a = h1.GetPoint(10);
    a.z += h1.GetStep();
    vec3 b = h1.GetPoint(10 + 2 * M_PI);
    std::cout << "a: " << a << ", b: " << b << "\n";

    

    double local_radii_sum = 0;
    double async_radii_sum = 0;

    auto res = std::async(std::launch::async, [&]()
    {
        for (std::size_t i = circles.size() / 2; i < circles.size(); ++i)
            async_radii_sum += circles[i]->GetRadius1();
    });

    for (std::size_t i = 0; i < circles.size() / 2; ++i)
        local_radii_sum += circles[i]->GetRadius1();

    res.wait();

    std::cout << "Total sum of radii: " << async_radii_sum + local_radii_sum << "\n";


    return 0;
}

void CreateRandomCurvesCollection(std::vector<std::shared_ptr<ICurve>>& curves_vector)
{
    std::mt19937_64 r(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<std::size_t> dis_vec_size(10, 30);
    std::uniform_int_distribution<std::size_t> dis_curve_type(0, 2);
    std::uniform_real_distribution<> dis_space(-10, 10);
    std::uniform_real_distribution<> dis_pos(0.00001, 10);

    curves_vector.clear();
    curves_vector.reserve(dis_vec_size(r));

    for (std::size_t i = 0; i < curves_vector.capacity(); ++i)
    {
        switch (dis_curve_type(r))
        {
        case 0:
            curves_vector.emplace_back(CurvesCreator::CreateCircle(dis_space(r),
                                                                   dis_space(r),
                                                                   dis_pos(r)));
            break;
        case 1:
            curves_vector.emplace_back(CurvesCreator::CreateEllipse(dis_space(r),
                                                                    dis_space(r),
                                                                    dis_pos(r),
                                                                    dis_pos(r)));
            break;
        case 2:
            curves_vector.emplace_back(CurvesCreator::CreateHelix(dis_space(r),
                                                                  dis_space(r),
                                                                  dis_space(r),
                                                                  dis_pos(r),
                                                                  dis_pos(r)));
            break;
        default: throw std::runtime_error("Unknown curve type");
        }
    }
}

void GetCirclesFromContainer(const std::vector<std::shared_ptr<ICurve>>& curves_vector,
                             std::vector<std::shared_ptr<Circle>>& circles_vector)
{
    circles_vector.clear();

    for (auto& curve : curves_vector)
    {
        //std::cout << typeid(*curve.get()).name() << "\n";

        auto circle = std::dynamic_pointer_cast<Circle>(curve);

        if (circle != nullptr) circles_vector.push_back(circle);
    }
}

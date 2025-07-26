#pragma once

#include <vector>

#include "constants.h"
#include "hittable.h"

class HittableList : public Hittable
{
    public:
        std::vector<shared_ptr<Hittable>> objects;

        HittableList() {}
        HittableList(shared_ptr<Hittable> obj) 
        {
            add(obj);
        }

        void clear()
        {
            objects.clear();
        }

        void add(shared_ptr<Hittable> obj)
        {
            objects.push_back(obj);
        }

        bool hit(const Ray& r, Interval t, HitRecord& rec) const override
        {
            HitRecord temp_rec;
            bool hit_obj = false;
            double closest = t.max;

            for (const auto& obj: objects)
            {
                if (obj->hit(r, Interval(t.min, closest), temp_rec))
                {
                    hit_obj = true;
                    closest = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_obj;
        }
};
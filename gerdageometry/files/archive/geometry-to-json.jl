using JSON

f = open(ARGS[1])
lines = readlines(f)

d = Dict()

for l in lines
    s = split(l)
    d[s[1]] = Dict{String, Any}(
                   "id" => parse(Int16, s[1]),
                   "name" => s[2],
                   "geometry-type" => parse(Int16, s[3]),
                   "radius-mm" => parse(Float64, s[5]),
                   "height-mm" => parse(Float64, s[6]),
                   "bulk-material" => s[20],
                   "bore-hole" => Dict(
                                       "radius-mm" => parse(Float64, s[4]),
                                       "depth-mm" => parse(Float64, s[7])
                                      ),
                   "dead-layer" => Dict(
                                        "inner-thickness-nm" => parse(Float64, s[8]),
                                        "outer-thickness-nm" => parse(Float64, s[9]),
                                        "top-thickness-nm" => parse(Float64, s[10]),
                                        "bottom-thickness-nm" => parse(Float64, s[11]),
                                        "material" => s[21]
                                        ),
                   "passivation-layer" => Dict(
                                         "thickness-nm" => parse(Float64, s[12]),
                                         "material" => s[22]
                                         ),
                   "groove" => Dict(
                                    "inner-radius-mm" => parse(Float64, s[13]),
                                    "outer-radius-mm" => parse(Float64, s[14]),
                                    "depth-mm" => parse(Float64, s[15]),
                                    "dead-layer-thickness-nm" => parse(Float64, s[16])
                                   ),
                   "segmentation" => Dict(
                                          "number-of-phi-segments" => parse(Int16, s[17]),
                                          "number-of-z-segments" => parse(Int16, s[18]),
                                          "angle-deg" => parse(Float64, s[19])
                                         )
                  )
end

for (key, val) in d
    if (val["geometry-type"] == 3 || val["geometry-type"] == 4 || val["geometry-type"] == 5)

        val["cone"] = Dict(
            "height-mm" => val["bore-hole"]["depth-mm"],
            "radius-deg" => val["segmentation"]["angle-deg"],
            "position" => val["segmentation"]["number-of-phi-segments"] == 0 ? "top" : "bottom"
        )
        if (val["cone"]["height-mm"] == 0 && val["cone"]["radius-deg"] == 0)
            delete!(val, "cone")
        end

        val["groove"] = Dict(
            "inner-radius-mm" => val["groove"]["inner-radius-mm"],
            "outer-radius-mm" => val["groove"]["outer-radius-mm"],
            "depth-mm" => val["groove"]["depth-mm"],
            "dead-layer-thickness-nm" => val["groove"]["dead-layer-thickness-nm"],
            "position" => val["segmentation"]["number-of-z-segments"] == 0 ? "bottom" : "top"
        )

        delete!(val, "bore-hole")
        delete!(val, "segmentation")

    end
end

d = Dict("gerdageometry" => d)

# remove null entries
for (k, v) in d["gerdageometry"]
    for (kk, vv) in v
        if typeof(vv) <: Dict
            for (kkk, vvv) in vv
                (vvv == 0) && delete!(vv, kkk)
            end
        else
            (vv == 0 && kk != "id") && delete!(v, kk)
        end
        if isempty(vv)
            delete!(v, kk)
        end
    end
end

open(ARGS[1][1:end-4] * ".json", "w") do fo
    JSON.print(fo, d, 4)
end

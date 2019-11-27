# GERDA geometry files format

Since September 2018, the geometry and matrix files must be encoded with the
JSON format. Keywords that have default values (see tables) can be omitted,
keywords with default value = n.a. are mandatory. See `files/geometry.json`
and `files/matrix-PhaseII-dec15.json`, for example.

*NOTE*: It's still possible to make use of the old `.dat` format by specifying
`/MG/geometry/detector/geometryfileformat dat` and
`/MG/geometry/detector/matrixfileformat dat` in your macro file.

## Geometry file

All the parameters concerning the geometry of the detectors are set under the
`gerdageometry` scope.

### Common settings

| keyword                          | type / default value    | notes                         |
| -------                          | ------                  | -----                         |
| `id`                             | `int` / n.a.            | detector ID (for matrix file) |
| `name`                           | `string` / n.a.         |                               |
| `geometry-type`                  | `int` / n.a.            | see [1]                       |
| `radius-mm`                      | `double` / n.a.         |                               |
| `height-mm`                      | `double` / n.a.         |                               |
| `bulk-material`                  | `string` / "EnrichedGe" |                               |
| `dead-layer/material`            | `string` / "EnrichedGe" |                               |
| `dead-layer/inner-thickness-nm`  | `double` / 0            |                               |
| `dead-layer/outer-thickness-nm`  | `double` / 0            |                               |
| `dead-layer/top-thickness-nm`    | `double` / 0            |                               |
| `dead-layer/bottom-thickness-nm` | `double` / 0            |                               |
| `groove/inner-radius-mm`         | `double` / 0            |                               |
| `groove/outer-radius-mm`         | `double` / 0            |                               |
| `groove/depth-mm`                | `double` / 0            |                               |
| `groove/dead-layer-thickness-nm` | `double` / 0            |                               |
| `passivation-layer/material`     | `string` / "EnrichedGe" |                               |

### `geometry-type` = 3, 4 and 5

| Keyword           | values              | notes |
| -------           | ------              | ----- |
| `groove/position` | `string` / "bottom" |       |
| `cone/position`   | `string` / "top"    |       |
| `cone/height-mm`  | `double` / 0        |       |
| `cone/radius-deg` | `double` / 0        |       |

### Other `geometry-type`s

| Keyword                               | values       | notes |
| -------                               | ------       | ----- |
| `bore-hole/radius-mm`                 | `double` / 0 |       |
| `bore-hole/depth-mm`                  | `double` / 0 |       |
| `segmentation/number-of-phi-segments` | `int` / 0    |       |
| `segmentation/number-of-z-segments`   | `int` / 0    |       |
| `segmentation/angle-deg`              | `double` / 0 |       |

## Matrix file

All the parameters concerning the composition of the array are set under the
`gerdamatrix` scope, see `matrix-PhaseII-dec15.json`, for example.

Each entry in `detector-ids` represents a string, each entry in
`detector-ids[n]` represents a slot in the string `n` and each entry in
`detector-ids[n][m]` represents a detector in the string `n` and in the slot `m`
(the ID specified in the geometry file must be used). Detector ID value -1 is
reserved for empty positions, -1 values at the end (bottom) of the string can be
omitted. At the time of writing, a maximum of 19 strings, 7 slots and 2
detectors per slot are allowed.

If the `/MG/geometry/detector/individualzposofdetectors` flag is set to `true`,
the lengths of the holder bars for each slot can be specified with the
`holder-bars-length-cm` keyword.

| Keyword                 | values                               | notes                                                     |
| -------                 | ------                               | -----                                                     |
| `detector-ids`          | `vector<vector<vector<int>>>` / n.a. |                                                           |
| `holder-bars-length-cm` | `vector<vector<double>>` / n.a.      | If `/MG/geometry/detector/individualzposofdetectors true` |

---
[1] Geometry types:

| `geometry-type` | Description                             |
| --------------- | --------------------------------------- |
| 1               | Non-true coaxial detectors (Phase I)    |
| 2               | True coaxial detectors (Phase II)       |
| 3               | Dummy BEGe for LAr instrumentation test |
| 4               | Individual BEGe for BEGe PhaseI string  |
| 5               | Individual BEGes for PhaseII            |
| 11              | Non-true coaxial detectors (PhaseII)    |

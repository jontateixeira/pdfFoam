/*---------------------------------------------------------------------------*\
                pdfFoam: General Purpose PDF Solution Algorithm
                   for Reactive Flow Simulations in OpenFOAM

 Copyright (C) 2012 Michael Wild, Heng Xiao, Patrick Jenny,
                    Institute of Fluid Dynamics, ETH Zurich
-------------------------------------------------------------------------------
License
    This file is part of pdfFoam.

    pdfFoam is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) version 3 of the same License.

    pdfFoam is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with pdfFoam.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Tetrahedron>
inline Foam::autoPtr<Tetrahedron>
Foam::tetFacePointCellDecomposition<Tetrahedron>::tetFromFacePointsCell
(
    const polyMesh& pMesh,
    label cellI,
    label cellFaceI,
    label facePointI
)
{
    const pointField& pMeshPoints = pMesh.points();
    const cell& c = pMesh.cells()[cellI];
    label faceI = c[cellFaceI];
    const face& f = pMesh.faces()[faceI];

    // avoid inside-out tets
    label ptBI = f[facePointI];
    label ptCI = f[f.rcIndex(facePointI)];
    if (cellI != pMesh.faceOwner()[faceI])
    {
        Swap(ptBI, ptCI);
    }

    return autoPtr<Tetrahedron>
    (
        new Tetrahedron
        (
            pMesh.faceCentres()[faceI],
            pMeshPoints[ptBI],
            pMeshPoints[ptCI],
            pMesh.cellCentres()[cellI]
        )
    );
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Tetrahedron>
inline const Foam::UList<Tetrahedron>&
Foam::tetFacePointCellDecomposition<Tetrahedron>::tetrahedra() const
{
    return tets_;
}

template<class Tetrahedron>
inline const Foam::labelListList&
Foam::tetFacePointCellDecomposition<Tetrahedron>::cellTetrahedra() const
{
    return cellTets_;
}

template<class Tetrahedron>
inline const Foam::labelList&
Foam::tetFacePointCellDecomposition<Tetrahedron>::tetrahedronFace() const
{
    return tetFace_;
}

template<class Tetrahedron>
inline const Foam::List<Foam::labelPair>&
Foam::tetFacePointCellDecomposition<Tetrahedron>::tetrahedronPoints() const
{
    return tetPoints_;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //

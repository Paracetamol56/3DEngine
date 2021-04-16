 <div class="mermaid">
    classDiagram
    class CApp {
    -m_mainFrame : CMain\*
    +CApp()
    +~CApp()
    +OnInit() virtual bool
    }

    class CMain {
    -m_mesh : CMesh
    -m_Near : float
    -m_Far : float
    -m_Fov : float
    -m_AspectRatio : float
    -m_FovRad : float
    -m_projMat : CMatrix4
    -m_rotMat : CMatrix4
    -m_thetaX : float
    -m_thetaZ : float
    +CMain()
    +~CMain()
    +update() void
    +updateRotation() void
    +OnKeyDown() void
    +OnResize() void
    }
    class CMatrix4 {
    -m_matrix : std::array<std::array<float, 4>, 4>
    +CMatrix4()
    +~CMatrix4()
    +getMatrix() std::array<std::array<float, 4>, 4>
    +getMatrixAt(size_t, size_t) float
    +setMatrixAt(size_t, size_t) void
    +operator*=(CMatrix4) CMatrix4&
    +operator*(CMatrix4) CMatrix4&
    +setZeros() CMatrix4&
    +setIdentity() CMatrix4&
    }

    class CMesh {
    -m_triangles : std::list<CTriangle>
    +CMatrix4()
    +~CMatrix4()
    getTrianlges() std::list<CTriangle>
    addTriangle(CTriangle) void
    }

    class CTriangle {
    -m_Points : std::array<CVector3D, 3>
    +CTriangle(CVector3D, CVector3D, CVector3D)
    +CTriangle(std::array<CVector3D, 3>)
    +CTriangle(CTriangle\*)
    +~CTriangle()
    getPoints() array<CVector3D, 3>
    setPoints(std::array<CVector3D, 3>) void
    }

    class CVector3D {
    -m_x float
    -m_y float
    -m_z float
    +CVector3D()
    +CVector3D(float, float, float)
    +~CVector3D()
    +getX() float
    +getY() float
    +getZ() float
    +setX(float) void
    +setY(float) void
    +setZ(float) void
    +operator-() CVector3D
    +operator+() CVector3D
    +operator+=(CVector3D&) CVector3D&
    +operator-=(CVector3D&) CVector3D&
    +operator*=(float) CVector3D&
    +operator/=(float) CVector3D&
    +operator+(CVector3D&)CVector3D&
    +operator-(CVector3D&) CVector3D&
    +operator*(float) CVector3D&
    +operator/(float) CVector3D&
    +operator*=(CMatrix4) CVector3D&
    +operator*(CMatrix4) CVector3D
    }

    CApp "1..1" --> "1..1" CMain

    CMain "1..1" --> "0..n" CMatrix4
    CMain "1..1" --> "0..1" CMesh

    CMain ..> CTriangle
    CMain ..> CVector3D
    CVector3D ..> CMatrix4

    CMesh "0..1" --> "0..n" CTriangle
    CTriangle "0..1" --> "3" CVector3D

</div>

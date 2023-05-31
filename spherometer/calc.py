import sympy as sy

# ball_size = 0.25
# a = 4.4475 - ball_size
# b = 4.5080 - ball_size
# c = 4.4725 - ball_size
# sagitta = 0.0235
# aperture = 6


def expr_k() -> sy.Symbol:
    """K-value."""
    a, b, c = sy.symbols("a, b, c")
    return (a+b+c)/2


def expr_r_s() -> sy.Symbol:
    """Radius of the spherometer."""
    a, b, c = sy.symbols("a, b, c")
    k = expr_k()
    return (a*b*c)/(4*sy.sqrt((k*(k-a)*(k-b)*(k-c))))


def expr_r_m() -> sy.Symbol:
    """Radius of the mirror."""
    s, d_b = sy.symbols("s, d_b")
    return (expr_r_s()**2 - s**2)/(2*s) - (d_b/2)


def expr_f() -> sy.Symbol:
    """Focal length of the mirror."""
    return expr_r_m()/2


def expr_f_ratio() -> sy.Symbol:
    """F-ratio of the mirror."""
    d = sy.symbols("d")
    return expr_f()/d


def expr_df() -> sy.Symbol:
    """Uncertainty in the focal length of the mirror."""
    s, a, b, c, ds, dx = sy.symbols("S, a, b, c, Delta_s, Delta_x")
    k = expr_k()
    r_s = expr_r_s()

    drsda = r_s/a - (a*b*c/8)*((-2*k**3 + (b+c)*k**2 + (a*b + a*c)*k - a*b*c/2)/(-k**4 + (a*b + a*c + b*c)*k**2 - k*a*b*c)**(3/2))
    drsdb = r_s/b - (a*b*c/8)*((-2*k**3 + (a+c)*k**2 + (b*a + b*c)*k - a*b*c/2)/(-k**4 + (a*b + a*c + b*c)*k**2 - k*a*b*c)**(3/2))
    drsdc = r_s/c - (a*b*c/8)*((-2*k**3 + (a+b)*k**2 + (c*b + c*a)*k - a*b*c/2)/(-k**4 + (a*b + a*c + b*c)*k**2 - k*a*b*c)**(3/2))

    return (1/2)*((r_s/s)*(drsda + drsdb + drsdc)*dx - ((r_s**2/(2*s**2)) + s)*ds)

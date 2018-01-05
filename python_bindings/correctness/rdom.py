import halide as hl

def test_rdom():
    x = hl.Var("x")
    y = hl.Var("y")

    diagonal = hl.Func("diagonal")
    diagonal[x, y] = 1

    domain_width = 10
    domain_height = 10

    r = hl.RDom(0, domain_width, 0, domain_height)
    r.where(r.x <= r.y)

    diagonal[r.x, r.y] += 2
    # Note that Realization is *not* implicitly convertible to Buffer
    # in the Python bindings, so we must explicitly grab the Buffer(s) we want
    output = diagonal.realize(domain_width, domain_height)[0]
    
    for iy in range(domain_height):
        for ix in range(domain_width):
            if ix <= iy:
                assert output[ix, iy] == 3
            else:
                assert output[ix, iy] == 1

    print("Success!")
    return 0

if __name__ == "__main__":
    test_rdom()

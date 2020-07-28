float4	matrix_vector_mul(t_matrix4 matrix, float4 vector)
{
		return (float4) (vector.x * matrix.s0 + vector.y * matrix.s1 + vector.z * matrix.s2,
						 vector.x * matrix.s4 + vector.y * matrix.s5 + vector.z * matrix.s6,
						 vector.x * matrix.s8 + vector.y * matrix.s9 + vector.z * matrix.sA,
						 0.0f);
}

float4	matrix_point_mul(t_matrix4 matrix, float4 point)
{
	return (float4) (point.x * matrix.s0 + point.y * matrix.s1 + point.z * matrix.s2 + matrix.s3,
					 point.x * matrix.s4 + point.y * matrix.s5 + point.z * matrix.s6 + matrix.s7,
					 point.x * matrix.s8 + point.y * matrix.s9 + point.z * matrix.sA + matrix.sB,
					 1.0f);
}

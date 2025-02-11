<?php
namespace App\Http\Controllers\Api;
use App\Http\Controllers\Controller;
use App\Models\Visit;
class ResetVisitsController extends Controller
{
    public function __invoke()
    {
        Visit::truncate();
        
        return response()->json();
    }
}